/**************************************************************************************************
	Common Functions
 
	Filename: common.h
	Project: AIR
	Author: Mike Gauthiere, Christopher Kitt, Karthik Raman
	Date: August 2008
	
**************************************************************************************************/

#include "common.h"

void clearArray(u08 *data, u32 data_len, u08 value)
// Writes 'value' to every byte of array 'data' for length 'data_len'
{
	u32 i;
	for(i = 0; i < data_len; i++) {
		data[i] = value;
	}
}

void printArrayHex(u08 *data, u32 data_len, u08 line_len)
// Prints the specified array 'data' of length 'data_len' as Hexadecimal
// characters using rprintf() with line breaks every 'line_len' characters
{
	u32 i;
	for(i = 0; i < data_len; i++) {
		rprintf("%02x ", data[i]);
		if(((i + 1) % line_len) == 0) {
			rprintfStr("\n");
		}
	}
	rprintfStr("\n\n");
}

void printArrayChar(u08 *data, u32 data_len, u08 line_len)
// Prints the specified array 'data' of length 'data_len' as ASCII
// characters using rprintf() with line breaks every 'line_len' characters
{
	u32 i;
	for(i = 0; i < data_len; i++) {
		rprintf("%01c ", data[i]);
		if(((i + 1) % line_len) == 0) {
			rprintfStr("\n");
		}
	}
	rprintfStr("\n\n");
}

u16 swapEnd16(u16 data)
// Byte-wise 16-bit (2-byte) Big Endian to Little Endian conversion, or vice-versa
{
	u16 out = 0;
	out += ((data & 0xFF00) >> 8);
	out += ((data & 0x00FF) << 8);
	return out;
}

u32 swapEnd32(u32 data)
// Byte-wise 32-bit (4-byte) Big Endian to Little Endian conversion, or vice-versa
{
	u32 out = 0;
	out += ((data & 0xFF000000) >> 24);
	out += ((data & 0x00FF0000) >> 8);
	out += ((data & 0x0000FF00) << 8);
	out += ((data & 0x000000FF) << 24);
	return out;
}

void pioInit(void)
// Initializes all leds as outputs, all switches as inputs & enables interrupt for PTT switch
{
	// Setup led outputs
	AT91C_BASE_PIOA->PIO_PER =  LED_MASK;  					// Peripheral enable
	AT91C_BASE_PIOA->PIO_OER =  LED_MASK;					// Output enable
	AT91C_BASE_PIOA->PIO_CODR = LED_MASK;					// Clear output
	
	// Setup switch inputs
	AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_PIOA;			// Enable clock for PIO
	AT91C_BASE_PIOA->PIO_ODR = SW_CONF_MASK | SW_PTT;		// Disable output for switch pins
	AT91C_BASE_PIOA->PIO_PER = SW_CONF_MASK | SW_PTT;		// PIO Enable for switch pins
	AT91C_BASE_PIOA->PIO_IFDR = ~(SW_CONF_MASK | SW_PTT);	// Input filter disable everthing that is not a switch
	AT91C_BASE_PIOA->PIO_IFER = SW_CONF_MASK | SW_PTT;		// Input filter enable all switches
	AT91C_BASE_PIOA->PIO_IER = SW_PTT;						// Enable interrupts on PTT switch
	
	// Configure interrupts
	processorAicAttach(AT91C_ID_PIOA, 6|AT91C_AIC_SRCTYPE_HIGH_LEVEL, pioIsr);		// the 6 is for the priority level, copied from
	//AT91C_BASE_PIOA->PIO_IER = SW_PTT;					// Enable interrupts for the PTT switch
	AT91C_BASE_PIOA->PIO_IER = SW_PTT | SW_CONF_MASK;	// Enable interrupts for all switches
	

	// Clear interrupts // not sure if this is the proper way to accomplish this -Mike
	int dummy;
	dummy = AT91C_BASE_PIOA->PIO_ISR;
	return;
}


void pioIsr(void)
// Interrupt Service Routine for Configuration Switches
{
	u32 int_status;
	u32 pio_status;
	
	
	int_status = AT91C_BASE_PIOA->PIO_ISR;		// Read the interrupt status register
	//int_status &=  AT91C_BASE_PIOA->PIO_IMR;		// Read the interrupt mask register
	pio_status =  AT91C_BASE_PIOA->PIO_PDSR;	// Read the pin data status register
	
	// PTT Button
	if(int_status & SW_PTT) {					// If the PTT button was activated
		if(pio_status & SW_PTT) {
			AT91C_BASE_PIOA->PIO_CODR = LED_RED;
			rprintfStr("PTT Button Released\n");
		} else {
			AT91C_BASE_PIOA->PIO_SODR = LED_RED;
			rprintfStr("PTT Button Pressed\n");
			char a[1];
			//ft(0, 512, &a);
		}
	}
	
	// CONF0 Switch
	if(int_status & SW_CONF0) {					// If the conf0 switch was activated
		if(pio_status & SW_CONF0) {
			rprintfStr("CONF 0 Switch On\n");
		} else {
			rprintfStr("CONF 0 Switch Off\n");
		}
	}
	
	// CONF1 Switch
	if(int_status & SW_CONF1) {					// If the conf1 switch was activated
		if(pio_status & SW_CONF1) {
			rprintfStr("CONF 1 Switch On\n");
		} else {
			rprintfStr("CONF 1 Switch Off\n");
		}
	}
	
	// CONF2 Switch
	if(int_status & SW_CONF2) {					// If the conf2 switch was activated
		if(pio_status & SW_CONF2) {
			rprintfStr("CONF 2 Switch On\n");
		} else {
			rprintfStr("CONF 2 Switch Off\n");
		}
	}
	
	// CONF3 Switch
	if(int_status & SW_CONF3) {					// If the conf3 switch was activated
		if(pio_status & SW_CONF3) {
			rprintfStr("CONF 3 Switch On\n");
		} else {
			rprintfStr("CONF 3 Switch Off\n");
		}
	}
	
	// clear AIC
	AT91C_BASE_AIC->AIC_EOICR = 0;
}

void pioWifiIsr(void)
// Interrupt Service Routine for USB WIFI's Host Controller (FIQ)
{
	
}

void pioFlashIsr(void)
// Interrupt Service Routine for USB Flash's Host Controller (INT0)
{
	
}

