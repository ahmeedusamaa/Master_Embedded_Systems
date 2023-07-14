/*
 * lcd_driver.c
 *
 *  Created on: Jul 11, 2023
 *      Author: ahmed osama
*/
#include "lcd_driver.h"

GPIO_PConfig_t PinCfg ;

void LCD_GPIO_init() {

}

void LCD_INIT()
{

}
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char character);
void LCD_WRITE_STRING(char* string);
void LCD_check_lcd_isbusy(void);
void LCD_lcd_kick(void);
void LCD_clear_screen();
void LCD_GOTO_XY(unsigned char line, unsigned char position);


