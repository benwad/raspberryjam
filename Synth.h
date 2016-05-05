#ifndef SYNTH_H
#define SYNTH_H

typedef struct
{
	float left_phase;
	float right_phase;
} FrameData;

class Synth {

	FrameData currentFrame;

	public:
		FrameData NextFrame();
		void WriteFrames(unsigned long numFrames, float* out);
};

#endif
