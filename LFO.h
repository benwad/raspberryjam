#pragma once

#define SAMPLE_RATE (44100)
#define TWO_PI 6.2831853

class LFO {

	private:
		float phaseIncrement; // how much to move the phase per frame, defined by wavelength
		float intensity;
		float phase;

	public:
		LFO() : phaseIncrement(0.1f), intensity(1.0f), phase(0.0f) {}
		void SetParams(
			float wavelength,
			float intensity
		);
		float NextFrame();
	
};
