#pragma once

#include <utility>

#include "Voice.h"
#include "Oscillator.h"
#include "ADSR.h"

class PolysynthVoice : public Voice {
    
	const static int numOscillators = 6;

    public:
        PolysynthVoice();
        ~PolysynthVoice() {};
		FrameData NextFrame();
		void SetNoteNumber(int noteNumber);
		void NoteOn();
		void NoteOff();
		bool IsActive();
		int GetNoteNumber();

    private:
		int noteNumber;
		float gain;
        ADSR envelope;
		std::pair<Oscillator, float> oscillators[numOscillators];
};
