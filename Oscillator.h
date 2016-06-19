#pragma once

#define SAMPLE_RATE (44100)
#define TWO_PI 6.2831853

#include "FrameData.h"

enum OscType {
	kOscillatorTypeSine,
	kOscillatorTypeSaw,
	kOscillatorTypeSquare
};

class Oscillator {

	private:
		FrameData currentFrame;
		float phase = 0.0f;
		float increment;
		OscType oscType = kOscillatorTypeSaw;

	public:
		FrameData NextFrame();
		void SetOscType(OscType oscType) { this->oscType = oscType; }
		void SetFrequency(float frequency);

};
