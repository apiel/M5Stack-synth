#ifndef INIT_APP_H_
#define INIT_APP_H_

#include <BluetoothA2DPSource.h>
#include <math.h>
#include <M5Core2.h>

#include "zic_note.h"
#include "zic_osc.h"
#include "ui/ui_key.h"
#include "zic_mod_asr.h"

BluetoothA2DPSource a2dp_source;
Zic_Osc osc;
Zic_Mod_Asr asr;

#define KEYS_COUNT 7 * 5
UI_Key keys[KEYS_COUNT] = {
    {0, 0, _C6}, {45, 0, _D6}, {90, 0, _E6}, {135, 0, _F6}, {180, 0, _G6}, {225, 0, _A6}, {270, 0, _B6}, {0, 45, _C5}, {45, 45, _D5}, {90, 45, _E5}, {135, 45, _F5}, {180, 45, _G5}, {225, 45, _A5}, {270, 45, _B5}, {0, 90, _C4}, {45, 90, _D4}, {90, 90, _E4}, {135, 90, _F4}, {180, 90, _G4}, {225, 90, _A4}, {270, 90, _B4}, {0, 135, _C3}, {45, 135, _D3}, {90, 135, _E3}, {135, 135, _F3}, {180, 135, _G3}, {225, 135, _A3}, {270, 135, _B3}, {0, 180, _C2}, {45, 180, _D2}, {90, 180, _E2}, {135, 180, _F2}, {180, 180, _G2}, {225, 180, _A2}, {270, 180, _B2}};

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

void displayKeyboard(uint8_t y)
{
    for (uint8_t k = 0; k < KEYS_COUNT; k++)
    {
        keys[k].render();
    }
}

void eventHandler(Event &e)
{
    // Serial.printf("%s %3d,%3d\n", e.typeName(), e.to.x, e.to.y);

    // TODO might need to find a better way, cause note on doesn't last
    // either fix ASR or find better UI handler 
    bool isOn = false;
    bool isOff = false;
    for (uint8_t k = 0; k < KEYS_COUNT; k++)
    {
        if (keys[k].update(e))
        {
            if (keys[k].isOn)
            {
                osc.frequency = NOTE_FREQ[keys[k].midiNote];
                asr.on();
                isOn = true;
            }
            else
            {
                isOff = true;
            }
        }
    }
    if (isOff && !isOn)
    {
        // only if there is not another note on
        asr.off();
    }
}

void initApp()
{
    Serial.begin(115200);
    Serial.println("Zic zic");

    M5.begin();
    M5.Lcd.fillScreen(BLACK);
    M5.background.addHandler(eventHandler, E_ALL);
    displayKeyboard(20);

    a2dp_source.start("Geo Speaker", get_data_channels);
    // asr.noSustain = true;

    // asr.on();
}

uint8_t count = 0;
void loopApp()
{
    M5.update();

    // osc.oscType = OSC_SINE;
    // delay(1000);
    // osc.frequency = NOTE_FREQ[_C3];
    // asr.on();
    // delay(1000);
    // osc.frequency = NOTE_FREQ[_D3];
    // asr.on();

    // osc.oscType = OSC_TRIANGLE;
    // delay(1000);
    // osc.frequency = NOTE_FREQ[_C3];
    // asr.on();
    // delay(1000);
    // osc.frequency = NOTE_FREQ[_D3];
    // asr.on();

    // // osc.oscType = OSC_SAW;
    // // delay(1000);
    // // osc.frequency = NOTE_FREQ[_C3];
    // // asr.on();
    // // delay(1000);
    // // osc.frequency = NOTE_FREQ[_D3];
    // // asr.on();

    // osc.oscType = OSC_NOIZE;
    // delay(1000);
    // osc.frequency = NOTE_FREQ[_C3];
    // asr.on();
    // delay(1000);
    // osc.frequency = NOTE_FREQ[_D3];
    // asr.on();

    // if (count > 5)
    // {
    //     if (count == 6)
    //     {
    //         Serial.println("End making noise");
    //     }
    //     osc.amplitude = 0;
    // }
    // count++;
}

#endif