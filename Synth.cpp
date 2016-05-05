#include "Synth.h"

FrameData Synth::NextFrame()
{
	this->currentFrame.left_phase += 0.02f;
	if (this->currentFrame.left_phase >= 1.0f) {
		this->currentFrame.left_phase -= 2.0f;
	}
	if (this->currentFrame.right_phase >= 1.0f) {
		this->currentFrame.right_phase -= 2.0f;
	}

	return this->currentFrame;
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
