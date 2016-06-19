#include "StringVoice.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "FrameData.h"
#include "MidiNotes.h"
#include "Oscillator.h"

StringVoice::StringVoice()
{
    this->envelope.SetParams(0, 220, 1.0f, 44100);
    // Fill the buffer with white noise
    srand(static_cast<unsigned> (time(0)));

    for (int i=0; i < this->bufferSize; i++) {
        this->refBuffer[i] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/2.0f)) - 1.0f;
    }

    this->Reset();
}

FrameData StringVoice::NextFrame()
{
    float frame = 0.0f;

    buffer[this->currentFrame] = \
        ((buffer[this->currentFrame] + buffer[this->currentFrame+1]) / 2.0f) * this->feedbackValue;

    frame = buffer[this->currentFrame] * this->gain * this->envelope.NextFrame();

    this->currentFrame++;
    if (this->currentFrame >= this->cycleSize) {
        this->currentFrame -= this->cycleSize;
    }

    else if (this->needsReset && !this->envelope.IsActive()) {
        this->Reset();
    }

    return FrameData(
        frame,
        frame
    );
}

void StringVoice::SetNoteNumber(int noteNumber) 
{
    this->noteNumber = noteNumber;

    this->cycleSize = SAMPLE_RATE / midiFrequencies[noteNumber];
}

void StringVoice::NoteOn()
{
    envelope.NoteOn();
}

void StringVoice::NoteOff()
{
    envelope.NoteOff();

    this->needsReset = true;
}

bool StringVoice::IsActive()
{
    return envelope.IsActive();
}

int StringVoice::GetNoteNumber()
{
    return this->noteNumber;
}

void StringVoice::Reset()
{
    std::copy(std::begin(this->refBuffer), std::end(this->refBuffer), this->buffer);
    this->currentFrame = 0;
    this->needsReset = false;
}

