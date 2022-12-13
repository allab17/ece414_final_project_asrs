#include <inttypes.h>
#include <xc.h>
#include "ts_lcd.h"
#include "TouchScreen.h"

const int32_t x_1 = 0;
const int32_t y_1 = 0;
const int32_t x_2 = 239;
const int32_t y_2 = 319;

const int32_t x1 = 160;
const int32_t y1 = 108;
const int32_t x2 = 864;
const int32_t y2 = 908;

uint8_t ts_lcd_get_ts(uint16_t *x, uint16_t *y) {
    //read the status of the touchscreen
    //return TRUE when a finger of stylus has been placed on the display, 2 pointer parameters assigned the current position in LCD coordinates
    struct TSPoint p;
    p.x = 0;
    p.y = 0;
    p.z = 0;
    getPoint(&p);
    *x = (((p.x-x1)*(x_2-x_1))/(x2-x1)) + x_1;
    *y = (((p.y-y1)*(y_2-y_1))/(y2-y1)) + y_1;
    if (p.z > 30) return 1;
    else return 0;
}

void ts_lcd_init() {
    
}

uint8_t pressed() {
    struct TSPoint p;
    p.x = 0;
    p.y = 0;
    p.z = 0;
    getPoint(&p);
    if (p.z > 30) return 1;
    else return 0;
}







