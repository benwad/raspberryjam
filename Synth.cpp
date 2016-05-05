#include "Synth.h"

Synth::Synth()
{
	this->SetFilterParams(1600.0f, 1.0f);
	this->filterEnv.SetParams(88200, 22050, 0.8f, 22050);
}

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
	this->SetFilterParams(this->filterEnv.NextFrame() * 44050.0f, 0.8f);

	float frameVal = this->filter.Run(this->currentFrame.left_phase * envValue);

	return FrameData(
		frameVal,
		frameVal
	);
}

void Synth::WriteFrames(unsigned long numFrames, float* out)
{
	for (unsigned long i=0; i<numFrames; i++)
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

void Synth::SetFilterParams(float cutoff, float q) {
	this->filter.Set(cutoff, q);
}

void Synth::NoteOn() {
	envelope.NoteOn();
	filterEnv.NoteOn();
}

void Synth::NoteOff() {
	envelope.NoteOff();
	filterEnv.NoteOff();
}
