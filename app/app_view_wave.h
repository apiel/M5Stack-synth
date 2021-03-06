#ifndef APP_VIEW_WAVE_H_
#define APP_VIEW_WAVE_H_

#include <M5Core2.h>

#include "app/app_tracks.h"

#include "ui/ui_component.h"
#include "ui/ui_color.h"
#include "ui/ui_knob.h"
#include "ui/ui_toggle.h"

class App_View_Wave : public UI_Component
{
protected:
    App_Tracks *tracks;

    UI_Knob knob;
    UI_Toggle togglePlay;
    UI_Toggle toggleMorph;

    void renderKnobValue()
    {
        M5.Lcd.fillRect(260, 0, 100, 30, UI_BACKGROUND);
        M5.Lcd.setCursor(270, 10);
        // more or less the same as ((float)wave->pos / (float)wave->sampleCount * 100) % 64
        // but not allowed by C++
        M5.Lcd.println(((int16_t)(tracks->synth->wave.pos / (float)tracks->synth->wave.sampleCount * 100) % 6400) * 0.01);

        // TODO display table ?
    }

public:
    App_View_Wave(App_Tracks *_tracks) : knob(160, 120, 100), togglePlay(10, 10), toggleMorph(10, 190)
    {
        tracks = _tracks;
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

    uint8_t update(Event &e)
    {
        if (knob.update(e))
        {
            if (toggleMorph.isOn)
            {
                tracks->synth->wave.pos += knob.direction;
            }
            else if (knob.step)
            {
                // TODO dont use 64 but wavetableCount
                // wave->pos = uint8_t(knob.value / 360.0f * 64) * wave->sampleCount;
                uint8_t pos = (uint16_t)(tracks->synth->wave.pos / (float)tracks->synth->wave.sampleCount) % 64;
                pos = (pos + knob.step) % 64;
                tracks->synth->wave.pos = pos * tracks->synth->wave.sampleCount;
            }
            // Serial.printf("knob value %d direction %d\n", knob.value, knob.direction);
            // for testing
            if (togglePlay.isOn)
            {
                if (knob.active)
                {
                    if (!tracks->synth->asr.isOn())
                    {
                        tracks->synth->asr.on();
                    }
                }
                else
                {
                    tracks->synth->asr.off();
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