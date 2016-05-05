#include <iostream>

#include "portaudio.h"

#define SAMPLE_RATE (44100)

typedef struct
{
	float left_phase;
	float right_phase;
} paTestData;

static paTestData data;

static int paCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
						const PaStreamCallbackTimeInfo *timeinfo,
						PaStreamCallbackFlags statusFlags,
						void *userData)
{
	paTestData *data = (paTestData*)userData;
	float *out = (float*)outputBuffer;
	unsigned int i;
	(void)inputBuffer; // prevent unused variable warning

	for (i=0; i<framesPerBuffer; i++)
	{
		*out++ = data->left_phase; // left
		*out++ = data->right_phase; // right

		// simple saw
		data->left_phase += 0.02f;
		// when signal reaches top, drop back down
		if (data->left_phase >= 1.0f) data->left_phase -= 2.0f;
		// higher pitch so we can distinguish left and right
		data->right_phase += 0.03f;
		if (data->right_phase >= 1.0f) data->right_phase -= 2.0f;
	}

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
								paCallback, // callback function
								&data );

	if (err != paNoError) {
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
		return 2;
	}

	std::cout << "Starting stream..." << std::endl;
	err = Pa_StartStream(stream);
	if (err != paNoError) {
		std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
		return 2;
	}

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
