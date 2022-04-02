#ifndef INIT_APP_H_
#define INIT_APP_H_

#include <BluetoothA2DPSource.h>
#include <math.h>

#include "zic_note.h"
#include "zic_osc.h"
#include "zic_mod_asr.h"

BluetoothA2DPSource a2dp_source;
Zic_Osc osc;
Zic_Mod_Asr asr;

int32_t get_data_channels(Frame *frame, int32_t channel_len)
{
    for (int sample = 0; sample < channel_len; ++sample)
    {
        osc.amplitudeMod = asr.next();

        frame[sample].channel1 = osc.next();
        frame[sample].channel2 = frame[sample].channel1;
    }

    return channel_len;
}

void initApp()
{
    Serial.begin(115200);
    Serial.println("Zic zic");

    a2dp_source.start("Geo Speaker", get_data_channels);
    asr.noSustain = true;
}

uint8_t count = 0;
void loopApp()
{
    osc.oscType = OSC_SINE;
    delay(1000);
    osc.frequency = NOTE_FREQ[_C3];
    asr.on();
    delay(1000);
    osc.frequency = NOTE_FREQ[_D3];
    asr.on();

    osc.oscType = OSC_TRIANGLE;
    delay(1000);
    osc.frequency = NOTE_FREQ[_C3];
    asr.on();
    delay(1000);
    osc.frequency = NOTE_FREQ[_D3];
    asr.on();

    if (count > 10)
    {
        if (count == 11) {
            Serial.println("End making noise");
        }
        osc.amplitude = 0;
    }
    count++;
}

#endif