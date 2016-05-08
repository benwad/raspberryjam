#pragma once

#include <mutex>

#include "WorkQueue.h"

class ArduinoInput {

	const char *portname = "/dev/cu.usbmodem1411";
	int fd;
	char buf[32];
	char numberBuf[4];
	WorkQueue<float>* cutoffQueue;

	public:

		ArduinoInput();
		void RunLoop();
		void SetQueue(WorkQueue<float>* queue) { this->cutoffQueue = queue; }

};
