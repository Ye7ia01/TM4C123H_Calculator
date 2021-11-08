#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "keypad.c"
#include "lcd.c"
#include "calc.c"
#include "rtc.c"
#include "eeprom.c"

/* structs */
struct contact
{
  uint8_t name[16]; // 16 bytes for name string
  uint8_t number[16]; // 16 byte for number string
};

/* Static Variables */
char input[16] = {'\0'}; // keypad input 
int input_index = 0; // keypad input array index
unsigned long int seconds;
struct contact write = {"name","number"}; // contact struct to ber written in EEPROM  
struct contact read = {"",""}; // contact struct to be read from EEPROM


/* Main Functions declaration */ 
void welcome_screen(void);    // print to LCD
void PortCIntHandler(void);  // keypad interrupt ISR
void enable_int(void); // keypad interrupt enabler
void handle_error(void); // calculator math errors handler (prints ERROR on LCD)

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif




int main(void)
{
  
    /* initializations */
    keypad_init();
    enable_int();
    lcd_init();
    rtc_init();
    eeprom_init();
    
    /* RTC usage test ( 5 SECONDS DELAY ) */
    lcd_write_string("   PROJECT X   ");
    while (HibernateRTCGet() <= 5) 
    {
      // wait 5 seconds
    }
    lcd_reset(); // reset LCD for ability to write
    HibernateRTCDisable();  // disable RTC
    
    /* EEPROM READ & WRITE TEST */
    EEPROMProgram((uint32_t *)&write, 0x000, sizeof(write)); // write contact struct
    EEPROMRead((uint32_t *)&read, 0x000, sizeof(read)); // read contact struct
    
    

    
    /* program loop */
    while(1)
    {
      SysCtlSleep(); // for low power consumption until interrupt 
    }
}
    
    
   

void enable_int()
{   
   GPIOIntTypeSet(KEYPAD_COL_PORT,KEYPAD_COL_PINS,GPIO_FALLING_EDGE); // set interrupts to FALLING EDGE ( as keypad charachter is 0 when pressed )
   GPIOIntRegister(KEYPAD_COL_PORT, PortCIntHandler); // set ISR as "PortCInHandler"
   GPIOIntEnable(KEYPAD_COL_PORT,KEYPAD_COL_PINS); // enable the interrupts on keypad colomn pins
}

void PortCIntHandler()
{   
    
    char key;
    char* final_result;
    key = read_keypad(); // read which char is pressed
    if (key == 0) 
    {
      return;
    }  
    
    /* IF '=' PRESSED */
    else if (key == '=') 
    {
      final_result = get_final_result(input); //compute equation
      if (final_result == 0)
      {
        handle_error(); // handle error if exist
      }
      else
      {
        lcd_write_result(final_result); // write anser if no errors
      }
      // wait for the RESET button to be pressed
      char wait = read_keypad();
      
      while (wait!='<')
      {
        wait = read_keypad();
      }
      
     }
    
    
     /* IF '<' PRESSED (reset) */
     else if (key == '<')
     {
       lcd_reset();
       for (int counter=0;counter<16;counter++)
         {
           input[counter] = '\0';
         }
       input_index = 0;
        
     }
      
     /* IF NUMBER OR OPERATOR IS PRESSED */ 
     else
     {
      lcd_data(key); // print 
      input[input_index] = key; // put char in input string
      input_index++;
     }    
     GPIOIntClear(KEYPAD_COL_PORT,KEYPAD_COL_PINS); // clear interrupt
     GPIOPinWrite(KEYPAD_ROW_PORT,KEYPAD_ROW_PINS,0x0F);

  
}

void welcome_scree()
{
   lcd_write_string("   PROJECT X   "); // print string to LCD
    while (HibernateRTCGet() <= 5) // wait 5 seconds with RTC
    {
    }
    lcd_reset(); // reset LCD for ability to write
    HibernateRTCDisable(); // stop RTC ( because it will continue counting even after power off)
}

void handle_error()
{
      lcd_write_string("CANNOT COMPUTE");
}


