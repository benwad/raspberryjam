#include "LFO.h"

#include <math.h>

void LFO::SetParams(float wavelength, float intensity)
{
	this->phaseIncrement = wavelength / SAMPLE_RATE;
	this->intensity = intensity;
}

float LFO::NextFrame()
{
	this->phase += this->phaseIncrement;
	if (this->phase > TWO_PI) {
		this->phase -= TWO_PI;
	}

	return sin(this->phase);
}
