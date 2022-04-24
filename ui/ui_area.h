#ifndef UI_AREA_H_
#define UI_AREA_H_

#include <M5Core2.h>

class UI_Area
{
public:
    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t w = 0;
    uint16_t h = 0;

    UI_Area() {}
    UI_Area(uint16_t _x, uint16_t _y, uint16_t _w, uint16_t _h)
    {
        set(_x, _y, _w, _h);
    }

    void set(uint16_t _x, uint16_t _y, uint16_t _w, uint16_t _h)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }

    bool in(Event &e)
    {
        return e.to.x > x && e.to.x < x + w && e.to.y > y && e.to.y < y + h;
    }
};

#endif
