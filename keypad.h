#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "tm4c123gh6pm.h"




#ifndef __KEYPAD_H__
#define __KEYPAD_H__

/* defines */
#define KEYPAD_PERIPHERALS     ( SYSCTL_PERIPH_GPIOD | SYSCTL_PERIPH_GPIOC )
#define KEYPAD_ROW_PORT GPIO_PORTD_BASE 
#define KEYPAD_COL_PORT GPIO_PORTC_BASE
#define KEYPAD_ROW_PERIPH SYSCTL_PERIPH_GPIOD
#define KEYPAD_COL_PERIPH SYSCTL_PERIPH_GPIOC
#define KEYPAD_ROW_PINS ( GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 )
#define KEYPAD_COL_PINS ( GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 )


const char keypad[4][4] = {{'1','2','3','*'},{'4','5','6','/'},{'7','8','9','+'},{'<','0','=','-'}}; 
void keypad_init(); // initialize keypad peripherals
char read_keypad(); // returns char pressed
#endif
