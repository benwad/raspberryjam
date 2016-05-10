#include <iostream>

#include "MidiInput.h"

#ifdef __platform_mac__
#define MIDI_DEVICE_ID 0
#else
#define MIDI_DEVICE_ID 3
#endif

MidiInput::MidiInput()
{
	PmError err;
	err = Pm_Initialize();
	if (err != pmNoError) {
		std::cout << "Error initializing: " << Pm_GetErrorText(err) << std::endl;
	}

	int numDevices = Pm_CountDevices();
	std::cout << numDevices << " devices" << std::endl;
	err = Pm_OpenInput(&(this->stream), 0, MIDI_DEVICE_ID, 128, 0, 0);
	if (err != pmNoError) {
		std::cout << "Error opening input: " << Pm_GetErrorText(err) << std::endl;
	}

	// We only want note on/off signals
	Pm_SetFilter(this->stream, !PM_FILT_NOTE);
}

MidiInput::~MidiInput()
{
	PmError err = Pm_Terminate();
	if (err != pmNoError) {
		std::cout << "Error terminating: " << Pm_GetErrorText(err) << std::endl;
	}
}

void MidiInput::RunLoop()
{
	int readResult = 0;
	PmEvent event;

	while(1)
	{
		readResult = Pm_Read(this->stream, &event, 1);
		if (readResult > 0) {
			MidiMessage msg(Pm_MessageData1(event.message), Pm_MessageData2(event.message));
			this->queue->Add(msg);
			if (readResult > 1) {
				std::cout << "More than one!" << std::endl;
			}
		}
	}
}

void MidiInput::SetQueue(WorkQueue<MidiMessage>* queue)
{
	this->queue = queue;
}
