#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#ifndef __LCD_H__
#define __LCD_H__


/* Defines */
#define LCD_PERIPHERALS   ( SYSCTL_PERIPH_GPIOA | SYSCTL_PERIPH_GPIOB )
#define LCD_DATA_PORT GPIO_PORTB_BASE
#define LCD_DATA_PINS ( GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 )
#define LCD_CONF_PORT GPIO_PORTA_BASE
#define LCD_CONF_PINS ( GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 )
#define RS            GPIO_PIN_5
#define RW            GPIO_PIN_6
#define E             GPIO_PIN_7



void lcd_init(); // initialize LCD peripherals
void lcd_cmd(char); // gives command to LCD 
void lcd_data(char); // prints char on LCD
void lcd_write_result(char*); // Prints equation result on LCD 
void lcd_write_string(char*); // prints given string on LCD (not same as "write_result" as result string is inverted)
void lcd_reset(); // resets LCD to be used more than one time
void delay_us(unsigned int); // makes delay in microseconds 
void delay_ms(unsigned int); // makes delay in milliseconds 

#endif