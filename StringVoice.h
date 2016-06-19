#pragma once

#include "Voice.h"
#include "ADSR.h"

class StringVoice : public Voice
{
    const static int bufferSize = 1024;

    private:
        float buffer[bufferSize];
        float refBuffer[bufferSize];
        float feedbackValue = 0.996f;
        int currentFrame = 0;
        int cycleSize = 220;
        float gain = 0.8f;
        int noteNumber;
        bool needsReset = false;
        ADSR envelope;

    public:
        StringVoice();
		FrameData NextFrame();
		void SetNoteNumber(int noteNumber) ;
		void NoteOn();
		void NoteOff();
		bool IsActive();
		int GetNoteNumber();

        void Reset(); // Reset the buffer
};
