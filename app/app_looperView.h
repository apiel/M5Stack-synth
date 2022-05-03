#ifndef APP_LOOPER_VIEW_H_
#define APP_LOOPER_VIEW_H_

#include <M5Core2.h>

#include "zic/zic_note.h"
#include "zic/zic_seq_loop.h"

#include "ui/ui_component.h"
#include "ui/ui_color.h"
#include "ui/ui_key.h"
#include "ui/ui_toggleLoop.h"

class App_LooperView : public UI_Component
{
protected:
    Zic_Seq_Loop *looper;

    static const uint8_t KEYS_COUNT = 7 * 3;
    static const uint8_t TOGGLE_COUNT = 4;

    UI_ToggleLoop toggles[TOGGLE_COUNT] = {{40, 35, 30},
                                           {120, 35, 30},
                                           {200, 35, 30},
                                           {280, 35, 30}};

    UI_Key keys[KEYS_COUNT] = {
        {0, 90, _C4}, {45, 90, _D4}, {90, 90, _E4}, {135, 90, _F4}, {180, 90, _G4}, {225, 90, _A4}, {270, 90, _B4}, {0, 135, _C3}, {45, 135, _D3}, {90, 135, _E3}, {135, 135, _F3}, {180, 135, _G3}, {225, 135, _A3}, {270, 135, _B3}, {0, 180, _C2}, {45, 180, _D2}, {90, 180, _E2}, {135, 180, _F2}, {180, 180, _G2}, {225, 180, _A2}, {270, 180, _B2}};

public:
    App_LooperView(Zic_Seq_Loop *_looper)
    {
        looper = _looper;
    }

    void render()
    {
        M5.Lcd.fillScreen(UI_BACKGROUND);
        for (uint8_t k = 0; k < KEYS_COUNT; k++)
        {
            keys[k].render();
        }

        for (uint8_t k = 0; k < TOGGLE_COUNT; k++)
        {
            toggles[k].render();
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
                    looper->on(keys[k].value);
                }
                else
                {
                    looper->off(keys[k].value);
                }
            }
        }
        for (uint8_t k = 0; k < TOGGLE_COUNT; k++)
        {
            if (toggles[k].update(e))
            {
                if (k == 0)
                {
                    looper->setLoopMode(toggles[k].isOn);
                }
            }
        }
        return false;
    }
};

#endif