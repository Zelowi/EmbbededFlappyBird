/*
 * ssd1306.c
 *
 *  Created on: Apr 29, 2026
 *      Author: Zelowi
 */

#include"ssd1306.h"
#include "stm32f407xx_i2c.h"

#include "ssd1306.h"


uint8_t buffer[1025];

const uint8_t ssd1306_init_cmds[] =
{
   0x00,

   0xAE,
   0xD5,0x80,
   0xA8,0x3F,
   0xD3,0x00,
   0x40 | 32,

   0x8D,0x14,

   0x20,0x00,

   0xA1,
   0xC0,

   0xDA,0x12,
   0x81,0x7F,

   0xA4,
   0xA6,

   0xAF
};

uint8_t set_area[7] = {
		  0x00,
		    0x21, 0, 127,
		    0x22, 0, 7
};

const uint8_t ssd1306_clear_byte[2] =
{
   0x40,
   0x00
};
void clear(uint8_t buffer[1025]){
	buffer[0] = 0x40;
	for(int i = 0;i < 1024;i++){
		buffer[i + 1] = 0;
	}
}
/*
void SSD1306_DrawPixel(uint8_t x, uint8_t y,uint8_t buffer[1025]){
	buffer[0] = 0x40;
	buffer[(y / 8) * 128 + x + 1] |= 1 << (y % 8);
}
*/

void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t buffer[1025])
{
    if(x >= 128 || y >= 64)
        return;

    y = y + SSD1306_Y_OFFSET;

    if(y >= 64)
        y -= 64;

    buffer[0] = 0x40;
    buffer[(y / 8) * 128 + x + 1] |= (1 << (y % 8));
}
