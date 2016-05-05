#include "Synth.h"

FrameData Synth::NextFrame()
{
	this->currentFrame.left_phase += increment;
	if (this->currentFrame.left_phase >= 1.0f) {
		this->currentFrame.left_phase -= 2.0f;
	}
	this->currentFrame.right_phase += increment;
	if (this->currentFrame.right_phase >= 1.0f) {
		this->currentFrame.right_phase -= 2.0f;
	}

	float envValue = this->envelope.NextFrame();

	return this->currentFrame * envValue;
}

void Synth::WriteFrames(unsigned long numFrames, float* out)
{
	for (int i=0; i<numFrames; i++)
	{
		FrameData nextFrame = this->NextFrame();

		*out++ = nextFrame.left_phase; // left
		*out++ = nextFrame.right_phase; // right
	}
}

void Synth::SetFrequency(unsigned int frequency)
{
	/*
	wavelength in frames: SAMPLE_RATE / frequency
	we want to increase by 2.0f per cycle
	so 2.0f / wavelength
	*/
	this->increment = 2.0f / (SAMPLE_RATE / frequency);
}

void Synth::NoteOn() {
	envelope.NoteOn();
}

void Synth::NoteOff() {
	envelope.NoteOff();
}
