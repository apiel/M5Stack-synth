#ifndef INIT_APP_H_
#define INIT_APP_H_

#include <BluetoothA2DPSource.h>
#include <math.h>
#include <M5Core2.h>

#include "initAudio.h"

#include "zic/zic_mod_asrNext.h"

#include "zic/zic_wave_wavetable.h"
#include "zic/zic_wavetable_SD.h"
#include "zic/wavetables/wavetable_Bank.h"
#include "zic/wavetables/wavetable_sine.h"

#include "app/app_def.h"
#include "app/app_keyboardView.h"
#include "app/app_waveView.h"
#include "app/app_menuView.h"
#include "app/app_settingsView.h"

#include "fastTrigo.h"

uint8_t previousMode = MODE_KEYBOARD;
uint8_t currentMode = MODE_KEYBOARD;
uint8_t mode = MODE_KEYBOARD;

BluetoothA2DPSource a2dp_source;

Zic_Wave_Wavetable wave(&wavetable_Bank);
// Zic_Wave_Wavetable wave(&wavetable_Sine);
Zic_Mod_AsrNext asr;

App_KeyboardView keyboardView(&wave, &asr);
App_WaveView waveView(&wave, &asr);
App_MenuView menuView(&mode);
App_SettingsView settingsView;

// void getSamples(int16_t *samples, uint32_t len)
// {
//     for (int i = 0; i < len; ++i)
//     {
//         wave.amplitudeMod = asr.next();
//         samples[i] = wave.next() * settingsView.volume.value;
//     }
// }

// TODO play sound from internal speaker
int32_t get_data_channels(Frame *frame, int32_t channel_len)
{
    for (int sample = 0; sample < channel_len; ++sample)
    {
        wave.amplitudeMod = asr.next();
        frame[sample].channel1 = wave.next() * settingsView.volume.value;
        frame[sample].channel2 = frame[sample].channel1;
    }

    return channel_len;
}

void playOnSpeaker()
{
    if (!a2dp_source.is_connected())
    {
        uint8_t data[1024];
        for (uint16_t i = 0; i < 1024; i++)
        {
            wave.amplitudeMod = asr.next();
            data[i] = wave.next();
        }
        size_t bytes_written = 0;
        i2s_write(Speak_I2S_NUMBER, data, 1024, &bytes_written, portMAX_DELAY);
    }
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
    else if (mode == MODE_SETTINGS)
    {
        settingsView.render();
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
        if (menuView.update(e))
        {
            previousMode = currentMode;
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
    else if (mode == MODE_SETTINGS)
    {
        settingsView.update(e);
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

    M5.Axp.SetSpkEnable(true);
    InitI2SSpeakOrMic(MODE_SPK);

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
            previousMode = currentMode;
        }
        else
        {
            currentMode = mode;
            mode = MODE_MENU;
        }
        render();
    }

    playOnSpeaker();
}

#endif