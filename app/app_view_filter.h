#ifndef APP_VIEW_FILTER_H_
#define APP_VIEW_FILTER_H_

#include <M5Core2.h>

#include "ui/ui_component.h"
#include "ui/ui_color.h"

class App_View_Filter : public UI_Component
{
protected:
    App_Tracks *tracks;

public:
    const uint16_t *color = &UI_THEME_ORANGE[0];

    App_View_Filter(App_Tracks *_tracks)
    {
        tracks = _tracks;
    }

    void render()
    {
        M5.Lcd.fillScreen(UI_BACKGROUND);
        M5.Lcd.fillCircle(150, 150, 5, color[1]);
    }

    uint8_t update(Event &e)
    {

        return false;
    }
};

#endif