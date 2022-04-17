#ifndef UI_KEY_H_
#define UI_KEY_H_

#include <M5Core2.h>

class UI_Key
{
protected:
    const uint8_t w = 45;
    const uint8_t h = 45;
    uint8_t midiNote = 60;

public:
    uint16_t x = 0;
    uint16_t y = 0;

    UI_Key(uint16_t _x, uint16_t _y, uint8_t _midiNote)
    {
        x = _x;
        y = _y;
        midiNote = _midiNote;
    }

    void render()
    {
        M5.Lcd.drawRect(x, y, w, h, BLUE);
    }

    void update()
    {
    }
};

#endif
