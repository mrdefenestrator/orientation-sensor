/**************************************************************************************************
	Common Functions
 
	Filename: common.h
	Project: AIR
	Author: Mike Gauthiere, Christopher Kitt, Karthik Raman
	Date: August 2008
	
	Description:___________________________________________________________________________________
		This is an implementation of several common functions that are useful throughout the code
		base.  It includes functions for clearing and printing arrays as well as switching the
		byte-endianness of 16 and 32 bit unsigned integers.
	
**************************************************************************************************/

#ifndef COMMON_H_
#define COMMON_H_

#include "rprintf.h"
#include "armlibtypes.h"
#include "at91sam7s256.h"
#include "airboard.h"
#include "processor.h"
#include "filethrower.h"

void clearArray(u08 *data, u32 data_len, u08 value);
void printArrayHex(u08 *data, u32 data_len, u08 line_len);
void printArrayChar(u08 *data, u32 data_len, u08 line_len);
u16 swapEnd16(u16);
u32 swapEnd32(u32);

void pioInit(void);

void pioIsr(void);
void pioWifiIsr(void);
void pioFlashIsr(void);


#endif /*COMMON_H_*/
