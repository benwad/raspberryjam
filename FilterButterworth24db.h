#pragma once

/*
	This is taken from "Butterworth Optimized C++ Class" by neotec on musicdsp.org
	http://musicdsp.org/showArchiveComment.php?ArchiveID=243
*/

struct FrameData;

class CFilterButterworth24db
{
public:
    CFilterButterworth24db(void);
    ~CFilterButterworth24db(void);
    void SetSampleRate(float fs);
    void Set(float cutoff, float q);
    float Run(float input);
    FrameData Run(FrameData input);

private:
    float t0, t1, t2, t3;
    float coef0, coef1, coef2, coef3;
    float history1, history2, history3, history4;
    float gain;
    float min_cutoff, max_cutoff;
	bool doStereo;
};
