#ifndef INIT_APP_H_
#define INIT_APP_H_

#include <BluetoothA2DPSource.h>
#include <math.h>
#include <M5Core2.h>

#include "initAudio.h"
#include "patterns.h"

#include "zic/zic_mod_asrNext.h"

#include "zic/zic_wave_wavetable.h"
#include "zic/zic_wavetable_SD.h"
#include "zic/wavetables/wavetable_Bank.h"
#include "zic/wavetables/wavetable_sine.h"
#include "zic/zic_seq_tempo.h"
#include "zic/zic_seq_loop.h"

#include "app/app_def.h"
#include "app/app_keyboardView.h"
#include "app/app_waveView.h"
#include "app/app_menuView.h"
#include "app/app_settingsView.h"
#include "app/app_looperView.h"

#include "fastTrigo.h"

uint8_t previousMode = MODE_LOOPER;
uint8_t currentMode = MODE_LOOPER;
uint8_t mode = MODE_LOOPER;

BluetoothA2DPSource a2dp_source;

Zic_Wave_Wavetable wave(&wavetable_Bank);
// Zic_Wave_Wavetable wave(&wavetable_Sine);
Zic_Mod_AsrNext asr;
Zic_Seq_Tempo<> tempo;
Zic_Seq_Loop looper(&patterns[2]);

App_KeyboardView keyboardView(&wave, &asr);
App_WaveView waveView(&wave, &asr);
App_MenuView menuView(&mode);
App_SettingsView settingsView;
App_LooperView looperView(&looper);

int16_t getSample()
{
    wave.amplitudeMod = asr.next();
    return wave.next() * settingsView.volume.value;
}

void getSamples(int16_t *samples, uint32_t len, uint8_t gain = 1)
{
    for (int i = 0; i < len; ++i)
    {
        samples[i] = getSample() * gain;
    }
}

int32_t getStereoSamples(Frame *frame, int32_t len)
{
    for (int sample = 0; sample < len; ++sample)
    {
        frame[sample].channel1 = getSample();
        frame[sample].channel2 = frame[sample].channel1;
    }
    return len;
}

// FIXME still not good sound
void playSpeaker()
{
    if (!a2dp_source.is_connected())
    {
        uint16_t len = 2048;
        int16_t samples[len];
        getSamples(&samples[0], len, 10);
        size_t bytes_written = 0;
        i2s_write(Speak_I2S_NUMBER, samples, len, &bytes_written, portMAX_DELAY);
    }
}

void render()
{
    if (mode == MODE_KEYBOARD)
    {
        keyboardView.render();
    }
    else if (mode == MODE_LOOPER)
    {
        looperView.render();
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

void sequencer()
{
    if (tempo.next(millis()))
    {
        looper.next();
        Zic_Seq_Step *stepOff = looper.getNoteOff();
        Zic_Seq_Step *stepOn = looper.getNoteOn();
        if (stepOff)
        {
            asr.off();
        }
        if (stepOn)
        {
            wave.frequency = NOTE_FREQ[stepOn->note];
            asr.on();
            Serial.printf("Note on %d\n", stepOn->note);
        }
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
    else if (mode == MODE_LOOPER)
    {
        looperView.update(e);
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
    // // or maybe we could just read the wavetable live from the file
    // M5.Lcd.println("Load wavetable bank...");
    // uint8_t ret = loadWavetableFromSD(&wavetable_Bank, "/01.wav");
    // Serial.printf("Load wavetable %d\n", ret);

    M5.background.addHandler(eventHandler, E_ALL);
    render();

    M5.Axp.SetSpkEnable(true);
    InitI2SSpeakOrMic(MODE_SPK);

    a2dp_source.start("Geo Speaker", getStereoSamples);

    // looper.setLoopMode(true);
    // looper.noteOn(_C3);
}

void loopApp()
{
    M5.update();
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

    sequencer();
    playSpeaker();
}

#endif