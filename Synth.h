#ifndef SYNTH_H
#define SYNTH_H

#define SAMPLE_RATE (44100)

#include "ADSR.h"

struct FrameData
{
	float left_phase;
	float right_phase;

	FrameData() : left_phase(0.0f), right_phase(0.0f) {};
	FrameData(float left_phase, float right_phase) : left_phase(left_phase), right_phase(right_phase) {}
	FrameData operator* (const float x) { return FrameData(left_phase * x, right_phase * x); }
};


class Synth {

	FrameData currentFrame;
	float increment;		// the increase in amplitude between two frames
	ADSR envelope;

	public:
		FrameData NextFrame();
		void WriteFrames(unsigned long numFrames, float* out);
		void SetFrequency(unsigned int frequency);
		void NoteOn();
		void NoteOff();
};

#endif
