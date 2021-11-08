#include "rtc.h"



void rtc_init()
{
	unsigned long ui32SysClock;
	ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
	SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000); // configure clock frequency
	SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE); // enable hibernation peripheral
	HibernateEnableExpClk(ui32SysClock); 
	HibernateClockConfig(HIBERNATE_OSC_LOWDRIVE); // configure clock for low oscillator
        HibernateRTCEnable(); // start the RTC seconds counter
}
