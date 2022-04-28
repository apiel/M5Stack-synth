#ifndef APP_SETTINGS_VIEW_H_
#define APP_SETTINGS_VIEW_H_

#include <M5Core2.h>

#include "app/app_def.h"

#include "ui/ui_component.h"
#include "ui/ui_color.h"
#include "ui/ui_slider.h"

class App_SettingsView : public UI_Component
{
public:
    UI_Slider volume;

    App_SettingsView() : volume(10, &UI_THEME_GREEN[0], "Volume")
    {
    }

    void render()
    {
        M5.Lcd.fillScreen(UI_BACKGROUND);
        volume.render();
    }

    bool update(Event &e)
    {
        volume.update(e);
        return false;
    }
};

#endif