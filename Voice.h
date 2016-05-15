#pragma once

#include "Oscillator.h"
#include "ADSR.h"

class Voice {

	private:
		ADSR envelope;
		Oscillator osc1;
		Oscillator osc2;
		Oscillator osc3;
		int noteNumber;

	public:
		FrameData NextFrame();
		void SetNoteNumber(int noteNumber);
		void NoteOn();
		void NoteOff();
		bool IsActive();
		int GetNoteNumber();
};
