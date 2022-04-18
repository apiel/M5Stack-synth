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

public:
    uint16_t y = 10;

    UI_Slider(uint16_t _y)
    {
        y = _y;
    }

    void render()
    {
        M5.Lcd.fillRoundRect(x, y, w, h, 7, UI_BLUE);
        M5.Lcd.fillCircle(100, y + circleRadius, circleRadius, UI_GREEN);
    }

    bool update(Event &e)
    {
        return false;
    }
};

#endif
