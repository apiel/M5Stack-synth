#ifndef UI_KNOB_H_
#define UI_KNOB_H_

#include <M5Core2.h>
#include <math.h>

#include "ui_color.h"
#include "ui_area.h"

class UI_Knob : protected UI_Area
{
public:
    UI_Knob(uint16_t _x, uint16_t _y)
    {
        x = _x;
        y = _y;
        w = 200;
        h = 200;
    }

    void render()
    {
        M5.Lcd.drawRect(x, y, w, h, UI_THEME_BLUE[0]);
    }

    bool update(Event &e)
    {
        if ((e.type == E_TOUCH || e.type == E_MOVE || e.type == E_RELEASE) && inArea(e))
        {
            int8_t _x = (e.to.x - x) - (w * 0.5);
            int8_t _y = (e.to.y - y) - (h * 0.5);

            // https://stackoverflow.com/questions/54280085/calculate-degrees-of-angle-using-x-y-coordinates
            int16_t degree = (int16_t)((atan2(_y, _x) * 180.0f / M_PI) + 360 + 90) % 360;

            M5.Lcd.fillRect(x + 5, y + 5 , 180, 100,  UI_BACKGROUND);
            M5.Lcd.setCursor(x + 10, y + 10);
            M5.Lcd.printf("%d x %d -> %d", _x, _y, degree);

            return true;
        }
        return false;
    }
};

#endif
