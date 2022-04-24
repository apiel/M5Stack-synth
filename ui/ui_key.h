#ifndef UI_KEY_H_
#define UI_KEY_H_

#include <M5Core2.h>

#include "ui_color.h"
#include "ui_area.h"

class UI_Key
{
protected:
    UI_Area area;

public:
    bool isOn = false;
    uint8_t midiNote = 60;

    UI_Key(uint16_t _x, uint16_t _y, uint8_t _midiNote)
    {
        area.set(_x, _y, 45, 45);
        midiNote = _midiNote;
    }

    void render()
    {
        if (isOn)
        {
            M5.Lcd.fillRect(area.x, area.y, area.w, area.h, UI_THEME_BLUE[1]);
        }
        else
        {
            M5.Lcd.fillRect(area.x, area.y, area.w, area.h, UI_BACKGROUND);
        }
        M5.Lcd.drawRect(area.x, area.y, area.w, area.h, UI_THEME_BLUE[0]);
    }

    bool update(Event &e)
    {
        if (e.type == E_TOUCH || e.type == E_MOVE || e.type == E_RELEASE)
        {
            if (e.type != E_RELEASE && area.in(e))
            {
                if (!isOn)
                {
                    isOn = true;
                    render();
                    return true;
                }
            }
            else if (isOn)
            {
                isOn = false;
                render();
                return true;
            }
        }
        return false;
    }
};

#endif
