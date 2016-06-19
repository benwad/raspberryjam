#include "PolysynthVoice.h"

#include "MidiNotes.h"

PolysynthVoice::PolysynthVoice()
{
	this->oscillators[0].second = 0.4f;
	this->oscillators[1].second = 0.2f;
	this->oscillators[2].second = 0.1f;
	this->oscillators[3].second = 0.1f;
	this->oscillators[4].second = 0.1f;
	this->oscillators[5].second = 0.1f;

	this->gain = 0.5f;
}

FrameData PolysynthVoice::NextFrame()
{
	float envValue = this->envelope.NextFrame();

	FrameData oscMix = FrameData(0.0f, 0.0f);

	for (int i=0; i < numOscillators; i++) {
		oscMix = oscMix + (oscillators[i].first.NextFrame() * oscillators[i].second);
	}

	return oscMix * (this->gain * envValue);
}

void PolysynthVoice::SetNoteNumber(int noteNumber)
{
	this->noteNumber = noteNumber;
	float fundamental = midiFrequencies[noteNumber];
	oscillators[0].first.SetFrequency(fundamental);
	for (int i=1; i < numOscillators; i++) {
		oscillators[i].first.SetFrequency(fundamental * (i+1));
	}
}

int PolysynthVoice::GetNoteNumber()
{
	return this->noteNumber;
}

void PolysynthVoice::NoteOn()
{
	envelope.NoteOn();
}

void PolysynthVoice::NoteOff()
{
	envelope.NoteOff();
}

bool PolysynthVoice::IsActive()
{
	return envelope.IsActive();
}
