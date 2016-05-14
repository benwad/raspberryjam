#include "Voice.h"

#include <iostream>

#include "MidiNotes.h"

FrameData Voice::NextFrame()
{
	float envValue = this->envelope.NextFrame();

	return this->osc1.NextFrame() * envValue;
}

void Voice::SetNoteNumber(int noteNumber)
{
	this->noteNumber = noteNumber;
	float freq = midiFrequencies[noteNumber];
	osc1.SetFrequency(freq);
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
