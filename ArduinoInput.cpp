#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "ArduinoInput.h"

ArduinoInput::ArduinoInput() {
	// Open the file descriptor in non-blocking mode
	this->fd = open(this->portname, O_RDWR | O_NOCTTY);

	/* Set up the control structure */
	struct termios toptions;

	/* Get currently set options for the tty */
	tcgetattr(this->fd, &toptions);

	/* Set custom options */
	/* 9600 baud */
	cfsetispeed(&toptions, B9600);
	cfsetospeed(&toptions, B9600);
	/* 8 bits, no parity, no stop bits */
	toptions.c_cflag &= ~PARENB;
	toptions.c_cflag &= ~CSTOPB;
	toptions.c_cflag &= ~CSIZE;
	toptions.c_cflag |= CS8;
	/* no hardware flow control */
	toptions.c_cflag &= ~CRTSCTS;
	/* enable receiver, ignore status lines */
	toptions.c_cflag |= CREAD | CLOCAL;
	/* disable input/output flow control, disable restart chars */
	toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
	/* disable canonical input, disable echo,
	disable visually erase chars,
	disable terminal-generated signals */
	toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	/* disable output processing */
	toptions.c_oflag &= ~OPOST;

	/* wait for 12 characters to come in before read returns */
	/* WARNING! THIS CAUSES THE read() TO BLOCK UNTIL ALL */
	/* CHARACTERS HAVE COME IN! */
	//toptions.c_cc[VMIN] = 12;
	toptions.c_cc[VMIN] = 1;
	/* no minimum time to wait before read returns */
	toptions.c_cc[VTIME] = 0;

	/* commit the options */
	tcsetattr(this->fd, TCSANOW, &toptions);

	/* Wait for the Arduino to reset */
	usleep(1000*1000);
	/* Flush anything already in the serial buffer */
	tcflush(this->fd, TCIFLUSH);

	memset(&this->numberBuf, 0, sizeof(char)*4);
}

void ArduinoInput::RunLoop() {
	int n;
	while(1) {
		// Read n bytes (up to 128) from this->fd into this->buf
		n = read(this->fd, this->buf, 128);
		for (int i=0; i < n; i++) {
			// If we've reached a newline, convert the input into
			// an integer and create a float between 0.0f and 1.0f
			// for the control value. Then reset the numberBuf
			if (this->buf[i] == '\n') {
				int potMessage = atoi(this->numberBuf);
				float potVal = potMessage / 1024.0;
				this->cutoffQueue->Add(potVal);
				memset(&this->numberBuf, 0, sizeof(char)*4);
			}
			else {
				// Otherwise, just store this buffer character
				// in the numberBuf
				for (int j=0; j<4; j++) {
					if (this->numberBuf[j] == (char)NULL) {
						this->numberBuf[j] = this->buf[i];
						break;
					}
				}
			}
		}
		//printf(buf);
	}
}
