#ifndef UI_KEY_H_
#define UI_KEY_H_

#include <M5Core2.h>

#define UI_BLUE M5.Lcd.color565(39, 69, 94)
#define UI_GREEN M5.Lcd.color565(73, 219, 158)

class UI_Key
{
protected:
    const uint8_t w = 45;
    const uint8_t h = 45;

public:
    uint16_t x = 0;
    uint16_t y = 0;
    bool isOn = false;
    uint8_t midiNote = 60;

    UI_Key(uint16_t _x, uint16_t _y, uint8_t _midiNote)
    {
        x = _x;
        y = _y;
        midiNote = _midiNote;
    }

    void render()
    {
        if (isOn)
        {
            M5.Lcd.fillRect(x, y, w, h, UI_GREEN);
        }
        else
        {
            M5.Lcd.fillRect(x, y, w, h, BLACK);
        }
        M5.Lcd.drawRect(x, y, w, h, UI_BLUE);
    }

    bool update(Event &e)
    {
        if (e.type == E_TOUCH || e.type == E_MOVE || e.type == E_RELEASE)
        {
            if (e.type != E_RELEASE && e.to.x > x && e.to.x < x + w && e.to.y > y && e.to.y < y + h)
            {
                if (!isOn)
                {
                    isOn = true;
                    render();
                    return true;
                }
            }
            else if (isOn)
            {
                isOn = false;
                render();
                return true;
            }
        }
        return false;
    }
};

#endif
