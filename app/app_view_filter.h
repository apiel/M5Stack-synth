#ifndef APP_VIEW_FILTER_H_
#define APP_VIEW_FILTER_H_

#include <M5Core2.h>

#include "ui/ui_component.h"
#include "ui/ui_color.h"

class App_View_Filter : public UI_Component
{
protected:
    App_Tracks *tracks;

    uint16_t lastX = 0;
    uint16_t lastY = 0;

public:
    const uint16_t *color = &UI_THEME_ORANGE[0];

    App_View_Filter(App_Tracks *_tracks)
    {
        tracks = _tracks;
    }

    void render()
    {
        M5.Lcd.fillScreen(UI_BACKGROUND);

        M5.Lcd.setCursor(5, 5);
        M5.Lcd.setTextColor(color[0], UI_BACKGROUND);
        M5.Lcd.println(tracks->synth->filter.getName());

        M5.Lcd.fillCircle(
            320 * tracks->synth->filter.cutoff,
            240 * tracks->synth->filter.resonance,
            5, color[1]);
    }

    uint8_t update(Event &e)
    {
        if ((e.type == E_TOUCH || e.type == E_MOVE) && (e.to.x != lastX || e.to.y != lastY))
        {
            lastX = e.to.x;
            lastY = e.to.y;
            float cutoff = lastX / 320.0f;
            float res = lastY / 240.0f;
            // Serial.printf("Update filter %d %d %.2f %.2f %s\n", lastX, lastY, cutoff, res, e.typeName());
            tracks->synth->filter.set(cutoff, res);
            render();
            return true;
        }
        return false;
    }

    void changeMode()
    {
        tracks->synth->filter.setFilterMode(tracks->synth->filter.mode + 1);
        render();
    }
};

#endif