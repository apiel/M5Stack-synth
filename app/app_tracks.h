#ifndef APP_TRACKS_H_
#define APP_TRACKS_H_

#include "app/app_def.h"

#include "app/app_audio_track.h"

#include "zic/wavetables/wavetable_Bank.h"
#include "zic/zic_wavetable_synth.h"
#include "zic/zic_seq_loop.h"

class App_Tracks
{
public:
    App_Audio_Track track0, track1, track2, track3;
    App_Audio_Track *tracks[TRACK_COUNT] = {&track0, &track1, &track2, &track3};
    App_Audio_Track *track = NULL;
    Zic_Wavetable_Synth *synth = NULL;
    Zic_Seq_Loop *looper = NULL;

    App_Tracks() : track0(TRACK_1), track1(TRACK_2), track2(TRACK_3), track3(TRACK_4)
    {
        select(TRACK_1);
    }

    void select(uint8_t id)
    {
        track = tracks[id % TRACK_COUNT];
        synth = &track->synth;
        looper = &track->looper;
    }

    void next()
    {
        for (uint8_t t = 0; t < TRACK_COUNT; t++)
        {
            tracks[t]->next();
        }
    }

    int16_t sample()
    {
        // 4 track seem to be too much
        return track0.synth.next() + track1.synth.next(); // + track2.synth.next() + track3.synth.next();
    }
};

#endif