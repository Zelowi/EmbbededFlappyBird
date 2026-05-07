/*
 * ssd1306.c
 *
 *  Created on: Apr 26, 2026
 *      Author: Zelowi
 */

#ifndef INC_SSD1306_C_
#define INC_SSD1306_C_

#include <stdint.h>

// =======================
// CONFIG
// =======================

#define SSD1306_WIDTH   128
#define SSD1306_HEIGHT  64

#define SSD1306_I2C_ADDR  0x3C   //

// Control bytes
#define SSD1306_COMMAND  0x00
#define SSD1306_DATA     0x40

// =======================
// API FUNCTIONS
// =======================

// Init display
extern const uint8_t ssd1306_init_cmds[];
extern  uint8_t set_area[7];
extern const uint8_t ssd1306_clear_byte[2];
#define SSD1306_INIT_SIZE 23
extern uint8_t buffer[1025];

#define OLED_ADDR 0x3C

#define SSD1306_Y_OFFSET 18

// Clear screen buffer + update display
void SSD1306_Clear(void);
void clear(uint8_t buffer[1025]);
void SSD1306_DrawPixel(uint8_t x, uint8_t y,uint8_t buffer[1025]);

// Update display (send buffer to OLED)
void SSD1306_Update(void);



// Draw single pixel


// Write character
void SSD1306_WriteChar(char c);

// Write string
void SSD1306_WriteString(char *str);

// Set cursor position
void SSD1306_SetCursor(uint8_t x, uint8_t y);




#endif /* INC_SSD1306_C_ */
