#pragma once

class ArduinoInput {

	float potVal;
	const char *portname = "/dev/cu.usbmodem1411";
	int fd;
	char buf[32];
	char numberBuf[4];

	public:
		ArduinoInput();
		float PotVal() { return this->potVal; }
		void RunLoop();

};
