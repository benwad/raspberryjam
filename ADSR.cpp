#include <iostream>

#include "ADSR.h"

ADSR::ADSR() {
	this->SetParams(44100, 88200, 0.9f, 44100);
	this->state = State::Off;
}

/*
	Attack, Decay and Release times are given in frames, SetParams
	converts them into per-frame deltas for use in NextFrame
*/
void ADSR::SetParams(	unsigned int attackTime,
						unsigned int decayTime,
						float sustain,
						unsigned int releaseTime ) {
	// Attack goes from 0.0f -> 1.0f in attackTime frames
	this->attackSpeed = 1.0f / attackTime;

	// Decay goes from 1.0f -> sustain in decayTime frames
	this->sustain = sustain;
	float decayDelta = 1.0f - sustain;
	this->decaySpeed = decayDelta / decayTime;

	// Release goes from sustain -> 0.0f in releaseTime frames
	this->releaseSpeed = sustain / releaseTime;
}

float ADSR::NextFrame() {
	switch (this->state) {
		case ADSR::State::Off:
			this->currentLevel = 0.0f;
			break;
		case ADSR::State::Attack:
			this->currentLevel += this->attackSpeed;
			if (this->currentLevel > 1.0f) {
				this->currentLevel = 1.0f;
				this->state = ADSR::State::Decay;
			}
			break;
		case ADSR::State::Decay:
			this->currentLevel -= this->decaySpeed;
			if (this->currentLevel < this->sustain) {
				this->currentLevel = this->sustain;
				this->state = ADSR::State::Sustain;
			}
			break;
		case ADSR::State::Sustain:
			this->currentLevel = this->sustain;
			break;
		case ADSR::State::Release:
			this->currentLevel -= this->releaseSpeed;
			if (this->currentLevel < 0.0f) {
				this->currentLevel = 0.0f;
				this->state = ADSR::State::Off;
			}
			break;
	}

	return this->currentLevel;
}

void ADSR::NoteOn() {
	this->state = ADSR::State::Attack;
}

void ADSR::NoteOff() {
	this->state = ADSR::State::Release;
}
