#pragma once

#define SAMPLE_RATE (44100)

#include "ADSR.h"
#include "LFO.h"
#include "FilterButterworth24db.h"
#include "WorkQueue.h"
#include "ArduinoMessage.h"
#include "MidiMessage.h"

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
	LFO filterLfo;
	WorkQueue<ArduinoMessage<float> >* cutoffQueue;
	WorkQueue<MidiMessage>* noteQueue;
	float cutoffVal;
	float resonanceVal;

	public:
		Synth();
		FrameData NextFrame();
		void WriteFrames(unsigned long numFrames, float* out);
		void SetCutoffQueue(WorkQueue<ArduinoMessage<float> >* queue);
		void SetNoteQueue(WorkQueue<MidiMessage>* queue);
		void SetFrequency(float frequency);
		void SetFilterParams(float cutoff, float q);
		void UpdateFilterParams();
		void NoteOn();
		void NoteOff();
};
