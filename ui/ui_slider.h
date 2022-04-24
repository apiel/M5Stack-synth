#ifndef UI_SLIDER_H_
#define UI_SLIDER_H_

#include <M5Core2.h>

#include "ui_color.h"
#include "ui_area.h"

// TODO option of sticky slider to middle or given position(s)
class UI_Slider
{
protected:
    const uint8_t circleRadius = 10;
    const char *name = NULL;
    UI_Area area;

public:
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
        area.set(10, _y, 300, circleRadius * 2);
        color = _color;
    }

    void render()
    {
        M5.Lcd.fillRoundRect(area.x, area.y, area.w, area.h, 7, color[0]);
        M5.Lcd.fillCircle(value * (area.w - circleRadius * 2) + (area.x + circleRadius), area.y + circleRadius, circleRadius - 1, color[1]);

        if (name)
        {
            M5.Lcd.setCursor(area.w - 50, area.y + 3);
            M5.Lcd.setTextColor(color[1], color[0]);
            M5.Lcd.println(name);
        }
    }

    bool update(Event &e)
    {
        // INFO might want to keep to respont to E_MOVE only if started to move slider in bar?
        // but in another way it's nice feature of be able to move just by passing over
        if ((e.type == E_TOUCH || e.type == E_MOVE) && area.in(e))
        {
            value = constrain((e.to.x - area.x - circleRadius) / (float)(area.w - circleRadius * 2), 0.0f, 1.0f);
            Serial.println(value);
            render();
            return true;
        }
        return false;
    }
};

#endif
