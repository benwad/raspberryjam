#ifndef SYNTH_H
#define SYNTH_H

#define SAMPLE_RATE (44100)

typedef struct
{
	float left_phase;
	float right_phase;
} FrameData;

class Synth {

	FrameData currentFrame;
	float increment;		// the increase in amplitude between two frames

	public:
		FrameData NextFrame();
		void WriteFrames(unsigned long numFrames, float* out);
		void SetFrequency(unsigned int frequency);
};

#endif
