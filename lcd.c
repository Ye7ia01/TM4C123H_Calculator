#include "lcd.h"

char final[16] = {'\0'};

void lcd_init()
{
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
 	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);       
	while(!SysCtlPeripheralReady(LCD_PERIPHERALS))
    {
    }
	GPIOPinTypeGPIOOutput(LCD_CONF_PORT,LCD_CONF_PINS);
	GPIOPinTypeGPIOOutput(LCD_DATA_PORT,LCD_DATA_PINS);
        delay_ms(20);
        lcd_cmd(0x30);
        delay_ms(5);
        lcd_cmd(0x30);
        delay_ms(1);
        lcd_cmd(0x30);
	lcd_cmd(0x38);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
	lcd_cmd(0x0F); 	
}

void lcd_cmd(char cmd)
{
	GPIOPinWrite(GPIO_PORTA_BASE,RS | RW,0x00);
	GPIOPinWrite(GPIO_PORTB_BASE,LCD_DATA_PINS,cmd);
	GPIOPinWrite(GPIO_PORTA_BASE,E,E);
	delay_us(100);
	GPIOPinWrite(GPIO_PORTA_BASE,E,0x00);
	delay_ms(2);
}

void lcd_data(char data)
{
	GPIOPinWrite(LCD_CONF_PORT,RW,0x00); // Set RW To 0
	GPIOPinWrite(LCD_CONF_PORT,RS,RS); // Set RS To 1 
	GPIOPinWrite(LCD_DATA_PORT,LCD_DATA_PINS,data);
	GPIOPinWrite(LCD_CONF_PORT,E,E); // PULSE E (HIGH)
	delay_us(100);
	GPIOPinWrite(LCD_CONF_PORT,E,0x00); // PULSE E (LOW)
	delay_ms(2);
}

void lcd_write_result(char* result)
{
        int j=0;
  	for (int i=strlen(result)-1;i>=0;i--)  
	{
		final[j] = result[i];
		j++;
	}
        lcd_cmd(0xC0);
        lcd_data('A');
        lcd_data('N');
        lcd_data('S');
        lcd_data('W');
        lcd_data('E');
        lcd_data('R');
        lcd_data(':');
  	for (int count=0;count<strlen(final);count++)
	{
		char x = final[count];
		lcd_data(x);
	}	
}

void lcd_write_string(char* string)
{
	lcd_cmd(0xC0);
	for (int count=0;count<strlen(string);count++)
	{
		char x = string[count];
		lcd_data(x);
	}	
}

void lcd_reset()
{
	lcd_cmd(0x01);
	lcd_cmd(0x80);
}

void delay_us(unsigned int n)
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<3;j++)
		{} 
	}
}

void delay_ms(unsigned int n)
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<3180;j++)
		{} 
	}
}





