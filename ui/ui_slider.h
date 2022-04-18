#ifndef UI_SLIDER_H_
#define UI_SLIDER_H_

#include <M5Core2.h>

#include "ui_color.h"

class UI_Slider
{
protected:
    const uint16_t w = 310;
    const uint8_t h = 20;
    const uint8_t x = 5;
    const uint8_t circleRadius = h * 0.5;
    const char *name = NULL;

public:
    uint16_t y = 10;
    const uint16_t *color;

    UI_Slider(uint16_t _y)
    {
        UI_Slider(_y, &UI_THEME_BLUE[0]);
    }

    UI_Slider(uint16_t _y, const uint16_t *_color)
    {
        UI_Slider(_y, _color, NULL);
    }

    UI_Slider(uint16_t _y, const uint16_t *_color, const char *_name)
    {
        name = _name;
        y = _y;
        color = _color;
    }

    void render()
    {
        M5.Lcd.fillRoundRect(x, y, w, h, 7, color[0]);
        M5.Lcd.fillCircle(100, y + circleRadius, circleRadius, color[1]);

        if (name)
        {
            M5.Lcd.setCursor(w - 50, y + 3);
            M5.Lcd.setTextColor(color[1], color[0]);
            M5.Lcd.println(name);
        }
    }

    bool update(Event &e)
    {
        return false;
    }
};

#endif
