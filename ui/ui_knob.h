#ifndef UI_KNOB_H_
#define UI_KNOB_H_

#include <M5Core2.h>
#include <math.h>

#include "ui_color.h"
#include "ui_area.h"

class UI_Knob
{
protected:
    bool active = false;
    uint8_t r = 0;
    uint16_t centerX = 0;
    uint16_t centerY = 0;
    UI_Area area;

    void calc(Event &e)
    {
        int8_t _x = (e.to.x - area.x) - (area.w * 0.5);
        int8_t _y = (e.to.y - area.y) - (area.h * 0.5);

        // https://stackoverflow.com/questions/54280085/calculate-degrees-of-angle-using-x-y-coordinates
        value = (int16_t)((atan2(_y, _x) * 180.0f / M_PI) + 360 + 90) % 360;

        M5.Lcd.fillRect(area.x + 5, area.y + 5, 180, 100, UI_BACKGROUND);
        M5.Lcd.setCursor(area.x + 10, area.y + 10);
        M5.Lcd.printf("%d x %d -> %d", _x, _y, value);
    }

public:
    int16_t value = 0;

    UI_Knob(uint16_t _x, uint16_t _y, uint8_t _r)
    {
        centerX = _x;
        centerY = _y;
        area.set(_x - _r, _y - _r, _r * 2, _r * 2);
        r = _r;
    }

    void render()
    {
        M5.Lcd.drawRect(area.x, area.y, area.w, area.h, UI_THEME_BLUE[0]);
        M5.Lcd.fillCircle(centerX, centerY, r, UI_THEME_BLUE[0]);
    }

    bool update(Event &e)
    {
        if (e.type == E_TOUCH && area.in(e))
        {
            calc(e);
            active = true;
            return true;
        }
        if (active)
        {
            if (e.type == E_RELEASE)
            {
                active = false;
            }
            if ((e.type == E_MOVE || e.type == E_RELEASE) && area.in(e))
            {
                calc(e);
                return true;
            }
        }
        return false;
    }
};

#endif
