#pragma once

class MidiMessage {

	int noteNum;
	int velocity;

	public:
		MidiMessage(int noteNum, int velocity)
			: noteNum(noteNum), velocity(velocity)
		{}

		int NoteNum() { return this->noteNum; }
		int Velocity() { return this->velocity; }
};
