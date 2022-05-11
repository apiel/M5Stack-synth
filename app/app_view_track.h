#ifndef APP_VIEW_TRACK_H_
#define APP_VIEW_TRACK_H_

#include <M5Core2.h>

#include "app/app_def.h"

#include "ui/ui_component.h"
#include "ui/ui_color.h"
#include "ui/ui_key.h"

#include "app/app_tracks.h"

class App_View_Track : public UI_Component
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
    App_Tracks *tracks;

    App_View_Track(App_Tracks *_tracks)
    {
        tracks = _tracks;
    }

    void render()
    {
        M5.Lcd.fillScreen(UI_BACKGROUND);
        for (uint8_t k = 0; k < KEYS_COUNT; k++)
        {
            keys[k].render();
        }
    }

    uint8_t update(Event &e)
    {
        for (uint8_t k = 0; k < KEYS_COUNT; k++)
        {
            if (keys[k].update(e))
            {
                keys[k].isOn = false;
                tracks->select(keys[k].value);
                return true;
            }
        }
        return false;
    }
};

#endif