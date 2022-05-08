#ifndef APP_VIEW_WAVE_H_
#define APP_VIEW_WAVE_H_

#include <M5Core2.h>

#include "zic/zic_wavetable_synth.h"

#include "ui/ui_component.h"
#include "ui/ui_color.h"
#include "ui/ui_knob.h"
#include "ui/ui_toggle.h"

class App_View_Wave : public UI_Component
{
protected:
    Zic_Wavetable_Synth *synth;

    UI_Knob knob;
    UI_Toggle togglePlay;
    UI_Toggle toggleMorph;

    void renderKnobValue()
    {
        M5.Lcd.fillRect(260, 0, 100, 30, UI_BACKGROUND);
        M5.Lcd.setCursor(270, 10);
        // more or less the same as ((float)wave->pos / (float)wave->sampleCount * 100) % 64
        // but not allowed by C++
        M5.Lcd.println(((int16_t)(synth->wave.pos / (float)synth->wave.sampleCount * 100) % 6400) * 0.01);

        // TODO display table ?
    }

public:
    App_View_Wave(Zic_Wavetable_Synth *_synth) : knob(160, 120, 100), togglePlay(10, 10), toggleMorph(10, 190)
    {
        synth = _synth;
    }

    void render()
    {
        M5.Lcd.fillScreen(UI_BACKGROUND);
        knob.render();
        // TODO use wave->pos to set knob.value

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
                synth->wave.pos += knob.direction;
            }
            else if (knob.step)
            {
                // TODO dont use 64 but wavetableCount
                // wave->pos = uint8_t(knob.value / 360.0f * 64) * wave->sampleCount;
                uint8_t pos = (uint16_t)(synth->wave.pos / (float)synth->wave.sampleCount) % 64;
                pos = (pos + knob.step) % 64;
                synth->wave.pos = pos * synth->wave.sampleCount;
            }
            // Serial.printf("knob value %d direction %d\n", knob.value, knob.direction);
            // for testing
            if (togglePlay.isOn)
            {
                if (knob.active)
                {
                    if (!synth->asr.isOn())
                    {
                        synth->asr.on();
                    }
                }
                else
                {
                    synth->asr.off();
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