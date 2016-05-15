#include "Voice.h"

#include <iostream>

#include "MidiNotes.h"

FrameData Voice::NextFrame()
{
	float envValue = this->envelope.NextFrame();

	FrameData oscMix = this->osc1.NextFrame() + this->osc2.NextFrame() + this->osc3.NextFrame();
	oscMix = oscMix / 3.0f;

	return oscMix * envValue;
}

void Voice::SetNoteNumber(int noteNumber)
{
	this->noteNumber = noteNumber;
	float fundamental = midiFrequencies[noteNumber];
	osc1.SetFrequency(fundamental);
	osc2.SetFrequency(fundamental * 2.0f);
	osc3.SetFrequency(fundamental * 3.0f);
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
