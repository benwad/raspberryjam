#include "Oscillator.h"

#include <iostream>

FrameData Oscillator::NextFrame()
{
	this->currentFrame.left_phase += increment;
	if (this->currentFrame.left_phase >= 1.0f) {
		this->currentFrame.left_phase -= 2.0f;
	}
	this->currentFrame.right_phase += increment;
	if (this->currentFrame.right_phase >= 1.0f) {
		this->currentFrame.right_phase -= 2.0f;
	}

	return this->currentFrame;
}

void Oscillator::SetFrequency(float frequency)
{
	/*
	wavelength in frames: SAMPLE_RATE / frequency
	we want to increase by 2.0f per cycle
	so 2.0f / wavelength
	*/
	this->increment = 2.0f / (SAMPLE_RATE / frequency);
}
