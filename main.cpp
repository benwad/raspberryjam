#include <iostream>

#include "portaudio.h"

#include "Synth.h"

//static FrameData data;
static Synth mySynth;

static int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
						const PaStreamCallbackTimeInfo *timeinfo,
						PaStreamCallbackFlags statusFlags,
						void *userData)
{
	//FrameData *data = (FrameData *)userData;
	float *out = (float*)outputBuffer;
	(void)inputBuffer; // prevent unused variable warning

	mySynth.WriteFrames(framesPerBuffer, out);

	return 0;
}

int main(int argc, char* argv[])
{
	PaStream *stream;
	PaError err;

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
								NULL );			// maybe use userData?

	if (err != paNoError) {
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
		return 2;
	}

	mySynth.SetFrequency(220);

	std::cout << "Starting stream..." << std::endl;
	err = Pa_StartStream(stream);
	if (err != paNoError) {
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
		return 2;
	}

	mySynth.NoteOn();

	std::cout << "Press ENTER to NoteOff..." << std::endl;
	getwchar();

	mySynth.NoteOff();

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
