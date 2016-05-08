#pragma once

#define SAMPLE_RATE (44100)

#include "ADSR.h"
#include "FilterButterworth24db.h"
#include "WorkQueue.h"

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
	CFilterButterworth24db filter;
	ADSR filterEnv;
	WorkQueue<float>* cutoffQueue;

	public:
		Synth();
		FrameData NextFrame();
		void WriteFrames(unsigned long numFrames, float* out);
		void SetCutoffQueue(WorkQueue<float>* queue);
		void SetFrequency(unsigned int frequency);
		void SetFilterParams(float cutoff, float q);
		void NoteOn();
		void NoteOff();
};
