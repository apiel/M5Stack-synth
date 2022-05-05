#ifndef APP_MENU_VIEW_H_
#define APP_MENU_VIEW_H_

#include <M5Core2.h>

#include "app/app_def.h"

#include "ui/ui_component.h"
#include "ui/ui_color.h"
#include "ui/ui_key.h"

class App_MenuView : public UI_Component
{
protected:
    static const uint8_t KEY_W = 80;
    static const uint8_t KEY_H = 80;
    static const uint8_t KEYS_COUNT = 4 * 3;

    // TODO add icon? using unicode ico? or GFX?
    // https://github.com/m5stack/FontCreator/blob/master/unicode2gfx.py
    // https://www.compart.com/en/unicode/category/So
    // https://unicode-table.com/fr/1F3B9/

    UI_Key keys[KEYS_COUNT] = {
        {0, 0, KEY_W, KEY_H, MODE_LOOPER, UI_THEME_PURPLE, "Looper"},
        {KEY_W, 0, KEY_W, KEY_H, MODE_WAVE, UI_THEME_PURPLE, "Wave"},
        {KEY_W * 2, 0, KEY_W, KEY_H, MODE_KEYBOARD, UI_THEME_PURPLE, "Keyboard"},
        {KEY_W * 3, 0, KEY_W, KEY_H, MODE_TRACK, UI_THEME_PURPLE, "Tracks"},
        {0, KEY_H, KEY_W, KEY_H, 4, UI_THEME_PURPLE},
        {KEY_W, KEY_H, KEY_W, KEY_H, 5, UI_THEME_PURPLE},
        {KEY_W * 2, KEY_H, KEY_W, KEY_H, 6, UI_THEME_PURPLE},
        {KEY_W * 3, KEY_H, KEY_W, KEY_H, 7, UI_THEME_PURPLE},
        {0, KEY_H * 2, KEY_W, KEY_H, 8, UI_THEME_PURPLE},
        {KEY_W, KEY_H * 2, KEY_W, KEY_H, 9, UI_THEME_PURPLE},
        {KEY_W * 2, KEY_H * 2, KEY_W, KEY_H, 10, UI_THEME_PURPLE},
        {KEY_W * 3, KEY_H * 2, KEY_W, KEY_H, MODE_SETTINGS, UI_THEME_PURPLE, "Settings"}};

public:
    uint8_t *mode;

    App_MenuView(uint8_t *_mode)
    {
        mode = _mode;
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
                *mode = keys[k].value;
                return true;
            }
        }
        return false;
    }
};

#endif