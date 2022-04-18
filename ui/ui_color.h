#ifndef UI_COLOR_H_
#define UI_COLOR_H_

#include <M5Core2.h>

#define UI_BACKGROUND BLACK

#define UI_THEME_SIZE 2
const uint16_t UI_THEME_BLUE[UI_THEME_SIZE] = {M5.Lcd.color565(39, 69, 94), M5.Lcd.color565(73, 219, 158)}; // 72, 182, 219
const uint16_t UI_THEME_PURPLE[UI_THEME_SIZE] = {M5.Lcd.color565(66, 39, 93), M5.Lcd.color565(219, 72, 219)};
const uint16_t UI_THEME_GREEN[UI_THEME_SIZE] = {M5.Lcd.color565(39, 93, 80), M5.Lcd.color565(182, 219, 72)};
const uint16_t UI_THEME_RED[UI_THEME_SIZE] = {M5.Lcd.color565(93, 39, 53), M5.Lcd.color565(219, 72, 72)};
const uint16_t UI_THEME_ORANGE[UI_THEME_SIZE] = {M5.Lcd.color565(93, 80, 39), M5.Lcd.color565(219, 219, 72)};

#endif
