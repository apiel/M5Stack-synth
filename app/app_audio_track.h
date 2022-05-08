#ifndef APP_AUDIO_TRACK_H_
#define APP_AUDIO_TRACK_H_

#include "patterns.h"

#include "zic/wavetables/wavetable_Bank.h"
#include "zic/zic_wavetable_synth.h"

class App_Audio_Track
{
public:
    Zic_Wavetable_Synth synth;
    Zic_Seq_Loop looper;

    App_Audio_Track() : synth(&wavetable_Bank), looper(&patterns[2])
    {
    }
};

#endif