#ifndef INIT_APP_H_
#define INIT_APP_H_

#include <BluetoothA2DPSource.h>
#include <math.h>
#include <M5Core2.h>

#include "zic/zic_mod_asrNext.h"

#include "zic/zic_wave_wavetable.h"
#include "zic/zic_wavetable_SD.h"
#include "zic/wavetables/wavetable_Bank.h"
#include "zic/wavetables/wavetable_sine.h"

#include "ui/ui_color.h"
#include "ui/ui_knob.h"
#include "ui/ui_toggle.h"

#include "app/app_keyboardView.h"

#include "fastTrigo.h"

BluetoothA2DPSource a2dp_source;

Zic_Wave_Wavetable wave(&wavetable_Bank);
// Zic_Wave_Wavetable wave(&wavetable_Sine);
Zic_Mod_AsrNext asr;

App_Keyboard keyboard(&wave, &asr);

enum
{
    OSC_SLIDER_CROSSFADER,
    OSC_SLIDER_COUNT
};

enum
{
    MODE_KEYBOARD,
    MODE_OSC,
    MODE_COUNT
};

uint8_t mode = MODE_KEYBOARD;

UI_Knob knob(160, 120, 100);
UI_Toggle togglePlay(10, 10);
UI_Toggle toggleMorph(10, 190);

// TODO play sound from internal speaker
int32_t get_data_channels(Frame *frame, int32_t channel_len)
{
    for (int sample = 0; sample < channel_len; ++sample)
    {
        wave.amplitudeMod = asr.next();
        frame[sample].channel1 = wave.next();
        frame[sample].channel2 = frame[sample].channel1;
    }

    return channel_len;
}

void renderKnobValue()
{
    M5.Lcd.fillRect(260, 0, 100, 30, UI_BACKGROUND);
    M5.Lcd.setCursor(270, 10);
    // more or less the same as ((float)wave.pos / (float)wave.sampleCount * 100) % 64
    // but not allowed by C++
    M5.Lcd.println(((int16_t)(wave.pos / (float)wave.sampleCount * 100) % 6400) * 0.01);

    // TODO display table ?
}

void displayOsc()
{
    M5.Lcd.fillScreen(UI_BACKGROUND);
    // for (uint8_t k = 0; k < OSC_SLIDER_COUNT; k++)
    // {
    //     oscSliders[k].render();
    // }
    knob.render();

    M5.Lcd.setCursor(25, 50);
    M5.Lcd.println("Play");
    togglePlay.render();

    M5.Lcd.setCursor(25, 177);
    M5.Lcd.println("Morph");
    toggleMorph.render();

    renderKnobValue();
}

void eventHandler(Event &e)
{
    // Serial.printf("%s %3d,%3d\n", e.typeName(), e.to.x, e.to.y);

    if (mode == MODE_KEYBOARD)
    {
        keyboard.update(e);
    }
    else if (mode == MODE_OSC)
    {
        // for (uint8_t k = 0; k < OSC_SLIDER_COUNT; k++)
        // {
        //     if (oscSliders[k].update(e))
        //     {
        //         if (k == OSC_SLIDER_CROSSFADER)
        //         {
        //             // wave.crossfader = oscSliders[k].value;
        //         }
        //     }
        // }
        if (knob.update(e))
        {
            if (toggleMorph.isOn)
            {
                wave.pos += knob.direction;
            }
            else if (knob.step)
            {
                // TODO dont use 64 but wavetableCount
                // wave.pos = uint8_t(knob.value / 360.0f * 64) * wave.sampleCount;
                uint8_t pos = (uint16_t)(wave.pos / (float)wave.sampleCount) % 64;
                pos = (pos + knob.step) % 64;
                wave.pos = pos * wave.sampleCount;
            }
            // Serial.printf("knob value %d direction %d\n", knob.value, knob.direction);
            // for testing
            if (!togglePlay.isOn)
            {
                if (knob.active)
                {
                    if (!asr.isOn())
                    {
                        asr.on();
                    }
                }
                else
                {
                    asr.off();
                }
            }
            renderKnobValue();
        }
        if (togglePlay.update(e))
        {
            if (togglePlay.isOn)
            {
                asr.on();
            }
            else
            {
                asr.off();
            }
        }
        toggleMorph.update(e);
    }
}

void render()
{
    if (mode == MODE_OSC)
    {
        displayOsc();
    }
    else
    {
        keyboard.render();
    }
}

void initApp()
{
    Serial.begin(115200);
    Serial.println("Zic zic");

    M5.begin();
    SD.begin();

    // // loading from SD is soooooooooo slow!!!!
    // // TODO see if we can load the wavetable in another thread
    // M5.Lcd.println("Load wavetable bank...");
    // uint8_t ret = loadWavetableFromSD(&wavetable_Bank, "/01.wav");
    // Serial.printf("Load wavetable %d\n", ret);

    M5.background.addHandler(eventHandler, E_ALL);
    render();

    a2dp_source.start("Geo Speaker", get_data_channels);
}

void loopApp()
{
    M5.update();
    // TODO might want to have a screen to select mode
    // long press display screen selector and select mode with dual touch
    // or should it be a short press bringing to mode screen?
    // ...
    // what the point to do dual touch, as it will be anyway pressing screen twice
    // once on screen mode selector, short press could also do something (go back)
    // as db press could do (toggle to prev screen)
    // as long press could do (?)
    if (M5.BtnA.wasPressed())
    {
        mode = (mode + 1) % MODE_COUNT;
        render();
    }
}

#endif