#ifndef APP_TRACK_VIEW_H_
#define APP_TRACK_VIEW_H_

#include <M5Core2.h>

#include "app/app_def.h"

#include "ui/ui_component.h"
#include "ui/ui_color.h"
#include "ui/ui_key.h"

class App_TrackView : public UI_Component
{
protected:
    static const uint8_t KEY_W = 160;
    static const uint8_t KEY_H = 120;
    static const uint8_t KEYS_COUNT = 2 * 2;

    UI_Key keys[KEYS_COUNT] = {
        {0, 0, KEY_W, KEY_H, TRACK_1, UI_THEME_GREEN, "Track 1"},
        {KEY_W, 0, KEY_W, KEY_H, TRACK_2, UI_THEME_GREEN, "Track 2"},
        {0, KEY_H, KEY_W, KEY_H, TRACK_3, UI_THEME_GREEN, "Track 3"},
        {KEY_W, KEY_H, KEY_W, KEY_H, TRACK_4, UI_THEME_GREEN, "Track 4"}};

public:
    uint8_t *track;

    App_TrackView(uint8_t *_track)
    {
        track = _track;
    }

    void render()
    {
        M5.Lcd.fillScreen(UI_BACKGROUND);
        for (uint8_t k = 0; k < KEYS_COUNT; k++)
        {
            keys[k].render();
        }
    }

    bool update(Event &e)
    {
        for (uint8_t k = 0; k < KEYS_COUNT; k++)
        {
            if (keys[k].update(e))
            {
                keys[k].isOn = false;
                *track = keys[k].value;
                return true;
            }
        }
        return false;
    }
};

#endif