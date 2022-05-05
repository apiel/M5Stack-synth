#ifndef APP_KEYBOARD_VIEW_H_
#define APP_KEYBOARD_VIEW_H_

#include <M5Core2.h>

#include "zic/zic_note.h"
#include "zic/zic_wavetable_synth.h"

#include "ui/ui_component.h"
#include "ui/ui_color.h"
#include "ui/ui_key.h"

class App_KeyboardView : public UI_Component
{
protected:
    Zic_Wavetable_Synth *synth;

    static const uint8_t KEYS_COUNT = 7 * 5;

    UI_Key keys[KEYS_COUNT] = {
        {0, 0, _C6}, {45, 0, _D6}, {90, 0, _E6}, {135, 0, _F6}, {180, 0, _G6}, {225, 0, _A6}, {270, 0, _B6}, {0, 45, _C5}, {45, 45, _D5}, {90, 45, _E5}, {135, 45, _F5}, {180, 45, _G5}, {225, 45, _A5}, {270, 45, _B5}, {0, 90, _C4}, {45, 90, _D4}, {90, 90, _E4}, {135, 90, _F4}, {180, 90, _G4}, {225, 90, _A4}, {270, 90, _B4}, {0, 135, _C3}, {45, 135, _D3}, {90, 135, _E3}, {135, 135, _F3}, {180, 135, _G3}, {225, 135, _A3}, {270, 135, _B3}, {0, 180, _C2}, {45, 180, _D2}, {90, 180, _E2}, {135, 180, _F2}, {180, 180, _G2}, {225, 180, _A2}, {270, 180, _B2}};

public:
    App_KeyboardView(Zic_Wavetable_Synth *_synth)
    {
        synth = _synth;
    }

    void render()
    {
        M5.Lcd.fillScreen(UI_BACKGROUND);
        for (uint8_t k = 0; k < KEYS_COUNT; k++)
        {
            keys[k].render();
        }
    }

    bool update(Event &e)
    {
        for (uint8_t k = 0; k < KEYS_COUNT; k++)
        {
            if (keys[k].update(e))
            {
                if (keys[k].isOn)
                {
                    synth->wave.frequency = NOTE_FREQ[keys[k].value];
                    synth->asr.on(keys[k].value);
                    // Serial.printf("Play note %d\n", keys[k].value);
                }
                else
                {
                    synth->asr.off(keys[k].value);
                }
            }
        }
        return false;
    }
};

#endif