#include <thread>
#include <iostream>

#include "WorkQueue.h"
#include "ArduinoInput.h"
#include "ArduinoMessage.h"


void readValues(WorkQueue<ArduinoMessage<float> >* queue)
{
	while(1) {
		if (queue->Size() > 0) {
			ArduinoMessage<float> msg = queue->Remove();
			std::cout << msg.messageType << ": " << msg.messageValue << std::endl;
		}
	}
}


int main(int argc, char* argv[])
{
	WorkQueue<ArduinoMessage<float> > queue;
	ArduinoInput input;
	input.SetQueue(&queue);

	std::thread controlThread(&ArduinoInput::RunLoop, input);
	std::thread readThread(&readValues, &queue);

	controlThread.detach();
	readThread.detach();

	std::cout << "Press ENTER to quit" << std::endl;

	getwchar();

	return 0;
	
}
