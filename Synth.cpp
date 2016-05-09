#include "Synth.h"

Synth::Synth()
	: cutoffVal(1600.0f),
	resonanceVal(0.8f)
{
	this->SetFilterParams(cutoffVal, resonanceVal);
	this->filterLfo.SetParams(1.0f, 1.0f);
}

FrameData Synth::NextFrame()
{
	this->currentFrame.left_phase += increment;
	if (this->currentFrame.left_phase >= 1.0f) {
		this->currentFrame.left_phase -= 2.0f;
	}
	this->currentFrame.right_phase += increment;
	if (this->currentFrame.right_phase >= 1.0f) {
		this->currentFrame.right_phase -= 2.0f;
	}

	float envValue = this->envelope.NextFrame();

	// See if we've got a new value from the input, and pop
	// it if we do
	if (this->cutoffQueue->Size() > 0) {
		ArduinoMessage<float> msg = this->cutoffQueue->Remove();
		if (msg.messageType == 0) {
			this->cutoffVal = msg.messageValue * 10000.0f;
		}
		else {
			float newWavelength = msg.messageValue * 20.0f;
			this->filterLfo.SetParams(newWavelength, 1.0f);
		}
	}

	this->UpdateFilterParams();

	// Check for notes
	if (this->noteQueue->Size() > 0) {
		MidiMessage msg = this->noteQueue->Remove();
		if (msg.Velocity() > 0) {
			this->SetFrequency(msg.NoteFrequency());
			this->NoteOn();
		}
		else {
			this->NoteOff();
		}
	}

	float frameVal = this->filter.Run(this->currentFrame.left_phase * envValue);

	return FrameData(
		frameVal,
		frameVal
	);
}

void Synth::WriteFrames(unsigned long numFrames, float* out)
{
	for (unsigned long i=0; i<numFrames; i++)
	{
		FrameData nextFrame = this->NextFrame();

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

void Synth::SetFrequency(float frequency)
{
	/*
	wavelength in frames: SAMPLE_RATE / frequency
	we want to increase by 2.0f per cycle
	so 2.0f / wavelength
	*/
	this->increment = 2.0f / (SAMPLE_RATE / frequency);
}

void Synth::SetFilterParams(float cutoff, float q)
{
	this->filter.Set(cutoff, q);
}

void Synth::UpdateFilterParams()
{
	float lfoValue = this->filterLfo.NextFrame();
	this->SetFilterParams(this->cutoffVal * lfoValue, this->resonanceVal);
}

void Synth::NoteOn()
{
	envelope.NoteOn();
}

void Synth::NoteOff()
{
	envelope.NoteOff();
}
