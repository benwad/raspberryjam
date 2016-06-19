#include "Synth.h"

#include "PolysynthVoice.h"

Synth::Synth()
	: cutoffVal(1600.0f),
	resonanceVal(0.5f)
{
	this->SetFilterParams(cutoffVal, resonanceVal);
	this->filterLfo.SetParams(1.0f, 0.5f);

	for (int i=0; i < this->numVoices; i++) {
		this->voices[i] = new PolysynthVoice();
	}
}

Synth::~Synth()
{
	for (int i=0; i < this->numVoices; i++) {
		delete this->voices[i];
	}
}

FrameData Synth::NextFrame()
{
	// See if we've got a new value from the input, and pop
	// it if we do
	if (this->cutoffQueue->Size() > 0) {
		ArduinoMessage<float> msg = this->cutoffQueue->Remove();
		if (msg.messageType == 0) {
			this->cutoffVal = msg.messageValue * 10000.0f;
		}
		else if (msg.messageType == 1) {
			float newWavelength = msg.messageValue * 20.0f;
			this->filterLfo.SetWavelength(newWavelength);
		}
		else if (msg.messageType == 2) {
			float newIntensity = msg.messageValue;
			this->filterLfo.SetIntensity(newIntensity);
		}
	}

	this->UpdateFilterParams();

	// Check for notes
	if (this->noteQueue->Size() > 0) {
		MidiMessage msg = this->noteQueue->Remove();
		if (msg.Velocity() > 0) {
			this->OnNoteOn(msg.NoteNum(), msg.Velocity());
		}
		else {
			this->OnNoteOff(msg.NoteNum(), msg.Velocity());
		}
	}

	FrameData currentFrame = FrameData(0.0f, 0.0f);
	float activeVoices = 0;

	// Mix together the voices and apply the filter
	for (int i=0; i < numVoices; i++) {
		if (voices[i]->IsActive()) {
			FrameData nextFrame = voices[i]->NextFrame();
			currentFrame = currentFrame + nextFrame;
			activeVoices += 1.0f;
		}
	}

	return this->filter.Run(currentFrame);
}

void Synth::WriteFrames(unsigned long numFrames, float* out)
{
	for (unsigned long i=0; i<numFrames; i++)
	{
		FrameData nextFrame = this->NextFrame();

		//std::cout << nextFrame.left_phase << std::endl;

		*out++ = nextFrame.left_phase; // left
		*out++ = nextFrame.right_phase; // right
	}
}

void Synth::SetCutoffQueue(WorkQueue<ArduinoMessage<float> >* queue)
{
	this->cutoffQueue = queue;
}

void Synth::SetNoteQueue(WorkQueue<MidiMessage>* queue)
{
	this->noteQueue = queue;
}

void Synth::OnNoteOn(int noteNumber, int velocity)
{
	Voice* voice = this->FindFreeVoice();

	voice->SetNoteNumber(noteNumber);
	voice->NoteOn();
}

void Synth::OnNoteOff(int noteNumber, int velocity)
{
	for (int i=0; i < this->numVoices; i++) {
		Voice* voice = this->voices[i];
		if (voice->IsActive() && voice->GetNoteNumber() == noteNumber) {
			voice->NoteOff();
		}
	}
}

void Synth::SetFilterParams(float cutoff, float q)
{
	this->filter.Set(cutoff, q);
}

void Synth::UpdateFilterParams()
{
	float lfoValue = this->filterLfo.NextFrame();
	float cutoffValue = this->cutoffVal * ((lfoValue + 1.0f) / 5.0f);
	this->SetFilterParams(cutoffValue, this->resonanceVal);
}

Voice* Synth::FindFreeVoice()
{
	Voice* freeVoice = NULL;
	for (int i=0; i < this->numVoices; i++) {
		if (!this->voices[i]->IsActive()) {
			freeVoice = this->voices[i];
			break;
		}
	}

	return freeVoice;
}
