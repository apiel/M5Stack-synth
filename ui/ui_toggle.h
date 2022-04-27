#ifndef UI_TOGGLE_H_
#define UI_TOGGLE_H_

#include <M5Core2.h>

#include "ui_color.h"
#include "ui_area_rect.h"

class UI_Toggle : public UI_Base
{
protected:
    UI_Area_Rect area;

public:
    bool isOn = false;
    uint8_t midiNote = 60;

    UI_Toggle(uint16_t _x, uint16_t _y) : area(_x, _y, 60, 35)
    {
    }

    void render()
    {
        M5.Lcd.fillRoundRect(area.x, area.y, area.w, area.h, area.h * 0.5, UI_THEME_BLUE[0]);
        if (isOn)
        {
            M5.Lcd.fillCircle(area.x + area.w - (area.h * 0.5 + 2), area.y + area.h * 0.5, area.h * 0.5 - 3, UI_THEME_BLUE[1]);
        }
        else
        {
            M5.Lcd.fillCircle(area.x + area.h * 0.5 + 1, area.y + area.h * 0.5, area.h * 0.5 - 3, UI_BACKGROUND);
        }
    }

    bool update(Event &e)
    {
        if (e.type == E_TOUCH && area.in(e))
        {
            isOn = !isOn;
            render();
            return true;
        }
        return false;
    }
};

#endif
