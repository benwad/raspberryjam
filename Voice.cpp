#include "Voice.h"

#include <iostream>

#include "MidiNotes.h"

Voice::Voice()
{
	oscillators[0].second = 0.4f;
	oscillators[1].second = 0.2f;
	oscillators[2].second = 0.1f;
	oscillators[3].second = 0.1f;
	oscillators[4].second = 0.1f;
	oscillators[5].second = 0.1f;
}

FrameData Voice::NextFrame()
{
	float envValue = this->envelope.NextFrame();

	FrameData oscMix = FrameData(0.0f, 0.0f);

	for (int i=0; i < numOscillators; i++) {
		oscMix = oscMix + (oscillators[i].first.NextFrame() * oscillators[i].second);
	}

	return oscMix * envValue;
}

void Voice::SetNoteNumber(int noteNumber)
{
	this->noteNumber = noteNumber;
	float fundamental = midiFrequencies[noteNumber];
	oscillators[0].first.SetFrequency(fundamental);
	for (int i=1; i < numOscillators; i++) {
		oscillators[i].first.SetFrequency(fundamental * (i+1));
	}
}

int Voice::GetNoteNumber()
{
	return this->noteNumber;
}

void Voice::NoteOn()
{
	envelope.NoteOn();
}

void Voice::NoteOff()
{
	envelope.NoteOff();
}

bool Voice::IsActive()
{
	return envelope.IsActive();
}
