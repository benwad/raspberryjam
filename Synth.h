#pragma once

#include "LFO.h"
#include "FilterButterworth24db.h"
#include "WorkQueue.h"
#include "ArduinoMessage.h"
#include "MidiMessage.h"
#include "Voice.h"

class Synth {

	static const int numVoices = 64;

	private:
		CFilterButterworth24db filter;
		LFO filterLfo;
		WorkQueue<ArduinoMessage<float> >* cutoffQueue;
		WorkQueue<MidiMessage>* noteQueue;
		Voice voices[numVoices];
		float cutoffVal;
		float resonanceVal;

	public:
		Synth();
		FrameData NextFrame();
		void WriteFrames(unsigned long numFrames, float* out);
		void SetCutoffQueue(WorkQueue<ArduinoMessage<float> >* queue);
		void SetNoteQueue(WorkQueue<MidiMessage>* queue);
		void OnNoteOn(int noteNumber, int velocity);
		void OnNoteOff(int noteNumber, int velocity);
		void SetFilterParams(float cutoff, float q);
		void UpdateFilterParams();
		Voice* FindFreeVoice();
};
