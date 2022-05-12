#ifndef APP_VIEW_LOOPER_H_
#define APP_VIEW_LOOPER_H_

#include <M5Core2.h>

#include <zic_note.h>
#include <zic_seq_loop.h>

#include "ui/ui_component.h"
#include "ui/ui_color.h"
#include "ui/ui_key.h"
#include "ui/ui_toggleLoop.h"

#include "app/app_tracks.h"

class App_View_Looper : public UI_Component
{
protected:
    App_Tracks *tracks;

    enum
    {
        LOOPER_MODE_KEYBOARD,
        LOOPER_MODE_PATTERNS,
        LOOPER_MODE_COUNT
    };

    uint8_t mode = LOOPER_MODE_KEYBOARD;

    static const uint8_t KEYS_COUNT = 7 * 3;
    static const uint8_t TOGGLE_COUNT = 4;

    UI_ToggleLoop toggles[TOGGLE_COUNT] = {{40, 35, 30, TRACK_1},
                                           {120, 35, 30, TRACK_2},
                                           {200, 35, 30, TRACK_3},
                                           {280, 35, 30, TRACK_4}};

    UI_Key keys[KEYS_COUNT] = {
        {0, 90, 0}, {45, 90, 1}, {90, 90, 2}, {135, 90, 3}, {180, 90, 4}, {225, 90, 5}, {270, 90, 6}, {0, 135, 7}, {45, 135, 8}, {90, 135, 9}, {135, 135, 10}, {180, 135, 11}, {225, 135, 12}, {270, 135, 13}, {0, 180, 14}, {45, 180, 15}, {90, 180, 16}, {135, 180, 17}, {180, 180, 18}, {225, 180, 19}, {270, 180, 20}};

    uint8_t lastKeyOn = 0;

    void renderToggles()
    {
        for (uint8_t k = 0; k < TOGGLE_COUNT; k++)
        {
            toggles[k].render();
        }
    }

    void renderMode()
    {
        M5.Lcd.fillRect(0, 78, 315, 12, UI_THEME_BLUE[0]);
        M5.Lcd.setTextColor(UI_THEME_BLUE[1], UI_THEME_BLUE[0]);
        if (mode == LOOPER_MODE_KEYBOARD)
        {
            M5.Lcd.setCursor(5, 80);
            M5.Lcd.println("Keyboard");
        }
        else if (mode == LOOPER_MODE_PATTERNS)
        {
            M5.Lcd.setCursor(255, 80);
            M5.Lcd.println("Patterns");
        }
    }

public:
    App_View_Looper(App_Tracks *_tracks)
    {
        tracks = _tracks;
        for (uint8_t k = 0; k < TOGGLE_COUNT; k++)
        {
            toggles[k].active = &tracks->trackId;
        }
    }

    void changeMode()
    {
        mode = (mode + 1) % LOOPER_MODE_COUNT;
        renderMode();
    }

    void render()
    {
        M5.Lcd.fillScreen(UI_BACKGROUND);
        // Serial.printf("nextToPlay %d\n", tracks->looper->nextToPlay);
        for (uint8_t k = 0; k < KEYS_COUNT; k++)
        {
            keys[k].render();
        }
        renderToggles();
        renderMode();
    }

    uint8_t update(Event &e)
    {
        for (uint8_t k = 0; k < KEYS_COUNT; k++)
        {
            if (keys[k].update(e))
            {
                if (keys[k].isOn)
                {
                    // FIXME NOT perfect but somehow work
                    keys[lastKeyOn].background = UI_BACKGROUND;
                    keys[lastKeyOn].render();
                    keys[k].background = UI_THEME_RED[0];
                    keys[k].render();
                    lastKeyOn = k;

                    tracks->looper->on(naturalNotesDown[keys[k].value + 28]); // 4*7 to start at C4
                }
                else
                {
                    tracks->looper->off(naturalNotesDown[keys[k].value + 28]);
                }
            }
        }
        for (uint8_t k = 0; k < TOGGLE_COUNT; k++)
        {
            uint8_t res = toggles[k].update(e);
            if (res == UI_TOOGLE_LOOP_TOGGLE)
            {
                tracks->looper->setLoopMode(toggles[k].isOn);
                return true;
            }
            else if (res == UI_TOOGLE_LOOP_ACTIVATE)
            {
                tracks->select(toggles[k].value);
                renderToggles();
                return true;
            }
        }
        return false;
    }
};

#endif