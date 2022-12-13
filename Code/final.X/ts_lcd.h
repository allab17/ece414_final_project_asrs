

/*============================================================================
 * TS_LCD_H
 *	Module for 
 * Author:
 *==========================================================================*/

#ifndef TS_LCD_H
#define	TS_LCD_H
#include <inttypes.h>

extern uint8_t ts_lcd_get_ts(uint16_t *x, uint16_t *y);

extern void ts_lcd_init();

#endif