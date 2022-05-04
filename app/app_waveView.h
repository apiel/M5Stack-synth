#ifndef APP_WAVE_VIEW_H_
#define APP_WAVE_VIEW_H_

#include <M5Core2.h>

#include "zic/zic_wave_wavetable.h"
#include "zic/zic_mod_asrNext.h"

#include "ui/ui_component.h"
#include "ui/ui_color.h"
#include "ui/ui_knob.h"
#include "ui/ui_toggle.h"

class App_WaveView : public UI_Component
{
protected:
    Zic_Wave_Wavetable *wave;
    Zic_Mod_AsrNext *asr;

    UI_Knob knob;
    UI_Toggle togglePlay;
    UI_Toggle toggleMorph;

    void renderKnobValue()
    {
        M5.Lcd.fillRect(260, 0, 100, 30, UI_BACKGROUND);
        M5.Lcd.setCursor(270, 10);
        // more or less the same as ((float)wave->pos / (float)wave->sampleCount * 100) % 64
        // but not allowed by C++
        M5.Lcd.println(((int16_t)(wave->pos / (float)wave->sampleCount * 100) % 6400) * 0.01);

        // TODO display table ?
    }

public:
    App_WaveView(Zic_Wave_Wavetable *_wave, Zic_Mod_AsrNext *_asr) : knob(160, 120, 100), togglePlay(10, 10), toggleMorph(10, 190)
    {
        wave = _wave;
        asr = _asr;
    }

    void render()
    {
        M5.Lcd.fillScreen(UI_BACKGROUND);
        knob.render();

        M5.Lcd.setCursor(25, 50);
        M5.Lcd.println("Play");
        togglePlay.render();

        M5.Lcd.setCursor(25, 177);
        M5.Lcd.println("Morph");
        toggleMorph.render();

        renderKnobValue();
    }

    bool update(Event &e)
    {
        if (knob.update(e))
        {
            if (toggleMorph.isOn)
            {
                wave->pos += knob.direction;
            }
            else if (knob.step)
            {
                // TODO dont use 64 but wavetableCount
                // wave->pos = uint8_t(knob.value / 360.0f * 64) * wave->sampleCount;
                uint8_t pos = (uint16_t)(wave->pos / (float)wave->sampleCount) % 64;
                pos = (pos + knob.step) % 64;
                wave->pos = pos * wave->sampleCount;
            }
            // Serial.printf("knob value %d direction %d\n", knob.value, knob.direction);
            // for testing
            if (togglePlay.isOn)
            {
                if (knob.active)
                {
                    if (!asr->isOn())
                    {
                        asr->on();
                    }
                }
                else
                {
                    asr->off();
                }
            }
            renderKnobValue();
        }
        togglePlay.update(e);
        toggleMorph.update(e);
        return false;
    }
};

#endif