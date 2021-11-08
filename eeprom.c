#include "eeprom.h"

void eeprom_init()
{
	uint32_t eeprom_init;
	SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0); // enable EEPROM peripheral
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0));
	eeprom_init = EEPROMInit();
	if (eeprom_init != EEPROM_INIT_OK ) // make sure EEPROM is ready
	{
		while(1);
	}
	
	
}
