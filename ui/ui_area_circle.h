#ifndef UI_AREA_CIRCLE_H_
#define UI_AREA_CIRCLE_H_

#include <M5Core2.h>

class UI_Area_Circle
{
public:
    uint8_t radius = 0;
    uint16_t x = 0;
    uint16_t y = 0;

    UI_Area_Circle() {}
    UI_Area_Circle(uint16_t _x, uint16_t _y, uint8_t _r)
    {
        set(_x, _y, _r);
    }

    void set(uint16_t _x, uint16_t _y, uint8_t _r)
    {
        x = _x;
        y = _y;
        radius = _r;
    }

    bool in(Event &e)
    {
        return abs(e.to.x - x) + abs(e.to.y - y) < abs(radius);
    }
};

#endif
