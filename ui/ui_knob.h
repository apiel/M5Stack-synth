#ifndef UI_KNOB_H_
#define UI_KNOB_H_

#include <M5Core2.h>
#include <math.h>

#include "ui_color.h"
#include "ui_circle.h"
#include "../fastTrigo.h"

class UI_Knob
{
protected:
    bool active = false;
    UI_Circle circle;

    uint16_t centerXpoint = 0;
    uint16_t centerYpoint = 0;

    void calc(Event &e)
    {
        int8_t _x = e.to.x - circle.x;
        int8_t _y = e.to.y - circle.y;

        // https://stackoverflow.com/questions/54280085/calculate-degrees-of-angle-using-x-y-coordinates
        value = (int16_t)((atan2(_y, _x) * 180.0f / M_PI) + 360) % 360;

        Serial.printf("%d x %d -> %d\n", _x, _y, value);

        renderKnobValue();
    }

    void renderKnobValue()
    {
        if (centerXpoint)
        {
            M5.Lcd.fillCircle(centerXpoint, centerYpoint, 3, UI_THEME_BLUE[0]);
        }

        float radian = M_PI * 2 * (float)value / 360.0f;
        uint8_t r2 = circle.radius - 10;
        centerXpoint = r2 * fastCos(radian) + circle.x;
        centerYpoint = r2 * fastSine(radian) + circle.y;
        // centerXpoint = r2 * cos(radian) + area.x + r;
        // centerYpoint = r2 * sin(radian) + area.y + r;
        M5.Lcd.fillCircle(centerXpoint, centerYpoint, 3, UI_THEME_BLUE[1]);
    }

public:
    int16_t value = 0;

    UI_Knob(uint16_t _x, uint16_t _y, uint8_t _radius) : circle(_x, _y, _radius)
    {
    }

    void render()
    {
        M5.Lcd.fillCircle(circle.x, circle.y, circle.radius, UI_THEME_BLUE[0]);
        M5.Lcd.drawCircle(circle.x, circle.y, circle.radius, UI_THEME_BLUE[1]);

        renderKnobValue();
    }

    bool update(Event &e)
    {
        if (e.type == E_TOUCH && circle.in(e))
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
            if ((e.type == E_MOVE || e.type == E_RELEASE) && circle.in(e))
            {
                calc(e);
                return true;
            }
        }
        return false;
    }
};

#endif
