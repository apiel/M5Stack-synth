#ifndef UI_KNOB_H_
#define UI_KNOB_H_

#include <M5Core2.h>
#include <math.h>

#include "ui_component.h"
#include "ui_color.h"
#include "ui_area_circle.h"
#include "../fastTrigo.h"

class UI_Knob : public UI_Component
{
protected:
    UI_Area_Circle circle;

    uint16_t centerXpoint = 0;
    uint16_t centerYpoint = 0;

    int8_t stepCounter = 0;

    void calc(Event &e)
    {
        int8_t _x = e.to.x - circle.x;
        int8_t _y = e.to.y - circle.y;

        prevValue = value;
        // https://stackoverflow.com/questions/54280085/calculate-degrees-of-angle-using-x-y-coordinates
        value = (int16_t)((atan2(_y, _x) * 180.0f / M_PI) + 360) % 360;

        // Serial.printf("%d x %d -> %d\n", _x, _y, value);
        calcDirection();
        calcStep();

        renderKnobValue();
    }

    void calcDirection()
    {
        if (prevValue > 350 && value < 10)
        {
            direction = (360 - prevValue) + value;
            return;
        }
        if (prevValue < 10 && value > 350)
        {
            direction = -((360 - value) + prevValue);
            return;
        }
        if (prevValue < value)
        {
            direction = value - prevValue;
            return;
        }
        direction = -(prevValue - value);
    }

    void calcStep()
    {
        stepCounter += direction;
        if (stepCounter >= stepGoal)
        {
            stepCounter = 0;
            step = 1;
        }
        else if (-stepCounter >= stepGoal)
        {
            stepCounter = 0;
            step = -1;
        }
        else
        {
            step = 0;
        }
        // Serial.printf("stepCounter %d, direction %d, step %d\n", stepCounter, direction, step);
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
    int16_t prevValue = 0;
    int16_t value = 0;
    int8_t direction = 0;
    // divide direction in bigger step so every 30° we get +1 or -1 step
    int8_t stepGoal = 30;
    int8_t step = 0;
    bool active = false;

    UI_Knob(uint16_t _x, uint16_t _y, uint8_t _radius) : circle(_x, _y, _radius)
    {
    }

    void render()
    {
        M5.Lcd.fillCircle(circle.x, circle.y, circle.radius, UI_THEME_BLUE[0]);
        M5.Lcd.drawCircle(circle.x, circle.y, circle.radius, UI_THEME_BLUE[1]);

        renderKnobValue();
    }

    uint8_t update(Event &e)
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
