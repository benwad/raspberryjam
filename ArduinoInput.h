#pragma once

#include <mutex>

#include "WorkQueue.h"
#include "ArduinoMessage.h"

class ArduinoInput {

	enum State {
		ReadingMessageType,
		ReadingMessageValue
	};

	const char *portname = "/dev/cu.usbmodem1411";
	int fd;
	char buf[32];
	char numberBuf[4];
	WorkQueue<ArduinoMessage<float> >* messageQueue;
	unsigned int messageType;

	public:

		ArduinoInput();
		void RunLoop();
		void SetQueue(WorkQueue<ArduinoMessage<float> >* queue) { this->messageQueue = queue; }

};
