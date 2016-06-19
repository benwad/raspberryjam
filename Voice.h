#pragma once

struct FrameData;

class Voice {

	public:
        virtual ~Voice() {};
		virtual FrameData NextFrame() = 0;
		virtual void SetNoteNumber(int noteNumber) = 0;
		virtual void NoteOn() = 0;
		virtual void NoteOff() = 0;
		virtual bool IsActive() = 0;
		virtual int GetNoteNumber() = 0;
};
