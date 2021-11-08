#include "keypad.h"


void keypad_init()
{
	
	SysCtlPeripheralEnable(KEYPAD_ROW_PERIPH); // enable ROW port peripherals
    SysCtlPeripheralEnable(KEYPAD_COL_PERIPH); // enable COL port peripherals
	while(!SysCtlPeripheralReady(KEYPAD_ROW_PERIPH | KEYPAD_COL_PERIPH))
        {
        }       
    GPIOPinTypeGPIOOutput(KEYPAD_ROW_PORT,KEYPAD_ROW_PINS); // set ROW pins as output
	GPIOPinTypeGPIOInput(KEYPAD_COL_PORT,KEYPAD_COL_PINS); // set COL pins as input
	GPIOPadConfigSet(KEYPAD_ROW_PORT,KEYPAD_ROW_PINS,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_OD); // sets ROW pins as OPEN DRAIN
	GPIOPadConfigSet(KEYPAD_COL_PORT,KEYPAD_COL_PINS,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU); // sets COL pins as PULL UP
    GPIOPinWrite(KEYPAD_ROW_PORT,KEYPAD_ROW_PINS,0x0F); // initialize ROW pins with 1s
}


char read_keypad()
{
	int row,col;
	uint32_t x;
        
	while(1)
	{
                
		row=0; // row 1
		GPIOPinWrite(KEYPAD_ROW_PORT,KEYPAD_ROW_PINS,0x0E); // set first ROW to 0 (ON)
		x = GPIOPinRead(KEYPAD_COL_PORT,KEYPAD_COL_PINS); // read COL pins 
		col = x & 0xF0;  // check for a short circuit
		if ( col != 0xF0 ) break; // if short circuit happens break 
		
		row=1; // row 2
		GPIOPinWrite(KEYPAD_ROW_PORT,KEYPAD_ROW_PINS,0x0D); // set second ROW to 0 (ON)
		x = GPIOPinRead(KEYPAD_COL_PORT,KEYPAD_COL_PINS); 
		col = x & 0xF0;
		if ( col != 0xF0 ) break;
		
		row=2;
		GPIOPinWrite(KEYPAD_ROW_PORT,KEYPAD_ROW_PINS,0x0B); // set third ROW to 0 (ON)
		x = GPIOPinRead(KEYPAD_COL_PORT,KEYPAD_COL_PINS);
		col = x & 0xF0;
		if ( col != 0xF0 ) break;
		
		row=3;
		GPIOPinWrite(KEYPAD_ROW_PORT,KEYPAD_ROW_PINS,0x07); // set fourth ROW to 0 (ON)
		x = GPIOPinRead(KEYPAD_COL_PORT,KEYPAD_COL_PINS);
		col = x & 0xF0;
		if ( col != 0xF0 ) break;
		
		return 0;
	}
		
	if ( col == 0xE0 ) { return keypad[row][0]; } // if short circuit occurs with COL pin 0
	if ( col == 0xD0 ) { return keypad[row][1]; } // if short circuit occurs with COL pin 1
	if ( col == 0xB0 ) { return keypad[row][2]; } // if short circuit occurs with COL pin 2
	if ( col == 0x70 ) { return keypad[row][3]; } // if short circuit occurs with COL pin 3
	return 0;
}







