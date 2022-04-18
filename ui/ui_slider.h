#ifndef UI_SLIDER_H_
#define UI_SLIDER_H_

#include <M5Core2.h>

#include "ui_color.h"

class UI_Slider
{
protected:
    const uint16_t w = 300;
    const uint8_t h = 20;
    const uint8_t x = 10;
    const uint8_t circleRadius = h * 0.5;
    const char *name = NULL;

public:
    uint16_t y = 10;
    const uint16_t *color;
    float value = 0.5f;

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
        M5.Lcd.fillCircle(value * (w - circleRadius * 2) + (x + circleRadius), y + circleRadius, circleRadius - 1, color[1]);

        if (name)
        {
            M5.Lcd.setCursor(w - 50, y + 3);
            M5.Lcd.setTextColor(color[1], color[0]);
            M5.Lcd.println(name);
        }
    }

    bool update(Event &e)
    {
        // INFO might want to keep to respont to E_MOVE only if started to move slider in bar?
        // but in another way it's nice feature of be able to move just by passing over
        if ((e.type == E_TOUCH || e.type == E_MOVE) && e.to.x > x && e.to.x < x + w && e.to.y > y && e.to.y < y + h)
        {
            value = constrain((e.to.x - x - circleRadius) / (float)(w - circleRadius * 2), 0.0f, 1.0f);
            Serial.println(value);
            render();
            return true;
        }
        return false;
    }
};

#endif
