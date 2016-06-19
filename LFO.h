#pragma once

class LFO {

	private:
		float phaseIncrement; // how much to move the phase per frame, defined by wavelength
		float intensity;
		float phase;

	public:
		LFO() : phaseIncrement(0.5f), intensity(1.0f), phase(0.0f) {}
		void SetWavelength(float wavelength);
		void SetIntensity(float intensity);
		void SetParams(
			float wavelength,
			float intensity
		);
		float NextFrame();
	
};
