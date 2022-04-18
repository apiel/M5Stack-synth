#ifndef UI_AREA_H_
#define UI_AREA_H_

#include <M5Core2.h>

class UI_Area
{
protected:
    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t w = 0;
    uint16_t h = 0;

    bool inArea(Event &e)
    {
        return e.to.x > x && e.to.x < x + w && e.to.y > y && e.to.y < y + h;
    }
};

#endif
