#ifndef ADSR_H
#define ADSR_H

class ADSR {
	enum State {
		Off,
		Attack,
		Decay,
		Sustain,
		Release
	};

	private:
		float attackSpeed;
		float decaySpeed;
		float sustain;
		float releaseSpeed;

		float currentLevel;

		State state;

	public:
		ADSR();
		void SetParams(
			unsigned int attackTime,
			unsigned int decayTime,
			float sustain,
			unsigned int releaseTime
		);
		float NextFrame();
		void NoteOn();
		void NoteOff();
};

#endif
