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

    void next()
    {
        looper.next();
        Zic_Seq_Step *stepOff = looper.getNoteOff();
        Zic_Seq_Step *stepOn = looper.getNoteOn();
        if (stepOff)
        {
            synth.asr.off();
        }
        if (stepOn)
        {
            synth.wave.frequency = NOTE_FREQ[stepOn->note];
            synth.asr.on();
        }
    }
};

#endif