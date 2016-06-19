#include "LFO.h"

#include "Oscillator.h"

#include <math.h>

void LFO::SetWavelength(float wavelength)
{
	this->phaseIncrement = wavelength / SAMPLE_RATE;
}

void LFO::SetIntensity(float intensity)
{
	this->intensity = intensity;
}

void LFO::SetParams(float wavelength, float intensity)
{
	this->SetWavelength(wavelength);
	this->SetIntensity(intensity);
}

float LFO::NextFrame()
{
	this->phase += this->phaseIncrement;
	if (this->phase > TWO_PI) {
		this->phase -= TWO_PI;
	}

	return this->intensity * sin(this->phase);
}
