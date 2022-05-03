#ifndef UI_TOGGLE_LOOP_H_
#define UI_TOGGLE_LOOP_H_

#include <M5Core2.h>

#include "ui_color.h"
#include "ui_area_rect.h"
#include "ui_component.h"

class UI_ToggleLoop : public UI_Component
{
protected:
    UI_Area_Rect area;

public:
    bool isOn = false;
    const uint16_t *color;
    uint16_t background = UI_BACKGROUND;

    UI_ToggleLoop(uint16_t _x, uint16_t _y, uint8_t _radius, const uint16_t *_color = &UI_THEME_RED[0])
        : area(_x - _radius, _y - _radius, _radius * 2, _radius * 2)
    {
        color = _color;
    }

    void render()
    {
        uint8_t radius = area.h * 0.5;
        M5.Lcd.fillCircle(area.x + radius, area.y + radius, radius, color[0]);
        if (isOn)
        {
            M5.Lcd.fillCircle(area.x + radius, area.y + radius, radius - 10, color[1]);
        }
        else
        {
            M5.Lcd.fillCircle(area.x + radius, area.y + radius, radius - 10, background);
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
