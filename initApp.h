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

#include "app/app_def.h"
#include "app/app_keyboardView.h"
#include "app/app_waveView.h"
#include "app/app_menuView.h"

#include "fastTrigo.h"

uint8_t previousMode = MODE_KEYBOARD;
uint8_t mode = MODE_KEYBOARD;

BluetoothA2DPSource a2dp_source;

Zic_Wave_Wavetable wave(&wavetable_Bank);
// Zic_Wave_Wavetable wave(&wavetable_Sine);
Zic_Mod_AsrNext asr;

App_KeyboardView keyboardView(&wave, &asr);
App_WaveView waveView(&wave, &asr);
App_MenuView menuView(&mode);

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

void render()
{
    if (mode == MODE_KEYBOARD)
    {
        keyboardView.render();
    }
    else if (mode == MODE_WAVE)
    {
        waveView.render();
    }
    else
    {
        menuView.render();
    }
}

void eventHandler(Event &e)
{
    // Serial.printf("%s %3d,%3d\n", e.typeName(), e.to.x, e.to.y);
    if (mode == MODE_MENU)
    {
        if (menuView.update(e)) {
            render();
        }
    }
    else if (mode == MODE_KEYBOARD)
    {
        keyboardView.update(e);
    }
    else if (mode == MODE_WAVE)
    {
        waveView.update(e);
    }
}

void initApp()
{
    Serial.begin(115200);
    Serial.println("Zic zic");

    M5.begin();
    SD.begin();

    Serial.println(M5.Lcd.width()); 

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
        if (mode == MODE_MENU)
        {
            mode = previousMode;
        }
        else
        {
            previousMode = mode;
            mode = MODE_MENU;
        }
        render();
    }
}

#endif