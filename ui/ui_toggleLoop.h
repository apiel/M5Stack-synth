#ifndef UI_TOGGLE_LOOP_H_
#define UI_TOGGLE_LOOP_H_

#include <M5Core2.h>

#include "ui_color.h"
#include "ui_area_rect.h"
#include "ui_component.h"

enum
{
    UI_TOOGLE_LOOP_NONE,
    UI_TOOGLE_LOOP_ACTIVATE,
    UI_TOOGLE_LOOP_TOGGLE,
};

class UI_ToggleLoop : public UI_Component
{
protected:
    UI_Area_Rect area;

    bool isActive()
    {
        bool yo = active && *active == value;
        Serial.printf("isActive: %d, %d == %d\n", yo, *active, value);
        return yo;
    }

public:
    bool isOn = false;
    uint8_t value = 0;
    uint8_t *active = NULL;

    const uint16_t *color;
    const uint16_t *activeColor;
    uint16_t background = UI_BACKGROUND;

    UI_ToggleLoop(uint16_t _x, uint16_t _y, uint8_t _radius, uint8_t _value = 0, uint8_t *_active = NULL,
                  const uint16_t *_color = &UI_THEME_RED[0], const uint16_t *_activeColor = &UI_THEME_GREEN[0])
        : area(_x - _radius, _y - _radius, _radius * 2, _radius * 2)
    {
        color = _color;
        activeColor = _activeColor;
        active = _active;
        value = _value;
    }

    void render()
    {
        uint8_t radius = area.h * 0.5;
        M5.Lcd.fillCircle(area.x + radius, area.y + radius, radius, isActive() ? activeColor[0] : color[0]);
        if (isOn)
        {
            M5.Lcd.fillCircle(area.x + radius, area.y + radius, radius - 10, isActive() ? activeColor[1] : color[1]);
        }
        else
        {
            M5.Lcd.fillCircle(area.x + radius, area.y + radius, radius - 10, background);
        }
    }

    // uint8_t update(Event &e)
    bool update(Event &e)
    {
        if (e.type == E_TOUCH && area.in(e))
        {
            if (isActive())
            {
                isOn = !isOn;
                render();
                // return UI_TOOGLE_LOOP_TOGGLE;
                return true;
            }
            else
            {
                // Serial.printf("active: %d\n", *active);
                // return UI_TOOGLE_LOOP_ACTIVATE;
                return true;
            }
        }
        // return UI_TOOGLE_LOOP_NONE;
        return false;
    }
};

#endif
