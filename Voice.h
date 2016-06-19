#pragma once

#include <utility>

#include "Oscillator.h"
#include "ADSR.h"

class Voice {

	const static int numOscillators = 6;

	private:
		ADSR envelope;
		std::pair<Oscillator, float> oscillators[numOscillators];
		int noteNumber;
		float gain;

	public:
		Voice();
		FrameData NextFrame();
		void SetNoteNumber(int noteNumber);
		void NoteOn();
		void NoteOff();
		bool IsActive();
		int GetNoteNumber();
};
