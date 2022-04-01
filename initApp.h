#ifndef INIT_APP_H_
#define INIT_APP_H_

#include <BluetoothA2DPSource.h>
#include <math.h>

#include "note.h"
#include "osc.h"

BluetoothA2DPSource a2dp_source;
Osc osc;

int32_t get_data_channels(Frame *frame, int32_t channel_len)
{
    for (int sample = 0; sample < channel_len; ++sample)
    {
        frame[sample].channel1 = osc.next();
        frame[sample].channel2 = frame[sample].channel1;
    }

    return channel_len;
}

void initApp()
{
    a2dp_source.start("Geo Speaker", get_data_channels);
}

void loopApp()
{
    // to prevent watchdog in release > 1.0.6
    delay(1000);
    osc.frequency = NOTE_FREQ[_C3];
    delay(1000);
    osc.frequency = NOTE_FREQ[_D3];
}

#endif