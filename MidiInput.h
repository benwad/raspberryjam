#pragma once

#include <portmidi.h>

#include "MidiMessage.h"
#include "WorkQueue.h"

class MidiInput {

	public:
		MidiInput();
		~MidiInput();
		void RunLoop();
		void SetQueue(WorkQueue<MidiMessage>* queue);

	private:
		PortMidiStream *stream;
		WorkQueue<MidiMessage> *queue;

};
