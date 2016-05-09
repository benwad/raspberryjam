#include <iostream>
#include <thread>

#include "portaudio.h"

#include "Synth.h"
#include "ArduinoInput.h"
#include "WorkQueue.h"
#include "MidiInput.h"
#include "MidiMessage.h"

static int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
						const PaStreamCallbackTimeInfo *timeinfo,
						PaStreamCallbackFlags statusFlags,
						void *userData)
{
	float *out = (float*)outputBuffer;
	(void)inputBuffer; // prevent unused variable warning

	Synth* mySynth = (Synth*)userData;
	mySynth->WriteFrames(framesPerBuffer, out);

	return 0;
}

void runmidi(WorkQueue<MidiMessage>* queue)
{
	MidiInput input;
	input.SetQueue(queue);
	input.RunLoop();
}

int main(int argc, char* argv[])
{
	PaStream *stream;
	PaError err;

	WorkQueue<MidiMessage> midiQueue;
	WorkQueue<ArduinoMessage<float> > cutoffQueue;
	ArduinoInput arduinoInput;
	arduinoInput.SetQueue(&cutoffQueue);
	Synth mySynth;
	mySynth.SetCutoffQueue(&cutoffQueue);
	mySynth.SetNoteQueue(&midiQueue);

	std::cout << "Initialising PortAudio..." << std::endl;
	err = Pa_Initialize();
	if (err != paNoError) {
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
		return 1;
	}

	std::cout << "Opening stream..." << std::endl;
	err = Pa_OpenDefaultStream( &stream,
								0,				// no input channels
								2,				// stereo output
								paFloat32,		// 32-bit floating point output
								SAMPLE_RATE,
								256,			// frames per buffer
								paCallback, 	// callback function
								&mySynth );		// pointer to Synth object

	if (err != paNoError) {
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
		return 2;
	}

	mySynth.SetFrequency(220.0f);

	std::cout << "Starting stream..." << std::endl;
	err = Pa_StartStream(stream);
	if (err != paNoError) {
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
		return 2;
	}

	std::thread midiThread(&runmidi, &midiQueue);
	midiThread.detach();
	std::thread controlThread(&ArduinoInput::RunLoop, arduinoInput);
	controlThread.detach();

	std::cout << "Press ENTER to exit..." << std::endl;
	getwchar();

	std::cout << "Stopping stream..." << std::endl;
	err = Pa_StopStream(stream);
	if (err != paNoError) {
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
		return 2;
	}

	err = Pa_Terminate();
	if (err != paNoError) {
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
		return 3;
	}

	return 0;
}
