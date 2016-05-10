#pragma once

#include <mutex>

#include "WorkQueue.h"
#include "ArduinoMessage.h"

#if __platform_mac__
#define PORTNAME "/dev/cu.usbmodem1411"
#else
#define PORTNAME "/dev/ttyACM0"
#endif

class ArduinoInput {

	enum State {
		ReadingMessageType,
		ReadingMessageValue
	};

	const char *portname = PORTNAME;
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
