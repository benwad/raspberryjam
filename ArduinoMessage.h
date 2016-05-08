#pragma once

template<typename T> class ArduinoMessage {

	public:
		unsigned int messageType;
		T messageValue;

		ArduinoMessage(unsigned int messageType, T messageValue)
			: messageType(messageType), messageValue(messageValue)
		{}
};
