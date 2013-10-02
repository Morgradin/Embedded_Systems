
/********************************************************************************
 * Driver Header
 ********************************************************************************/

#ifndef DRIVER_H
#define DRIVER_H

#include "types.h"

enum addresses {
	/* CCD addresses / commands */
	CCDCapture = 0x10000002,
	CCDReset = 0x10000003,
	CCDGetWidth = 0x10000004,
	CCDGetHeight = 0x10000005,
	CCDGetPixel = 0x10000006,
	CCDGetPixels = 0x10000007,

	/* LCD addresses / commands */
	LCDShow = 0x20000002,
	LCDReset = 0x20000003,
	LCDSetWidth = 0x20000004,
	LCDSetHeight = 0x20000005,
	LCDSetPixel = 0x20000006,
	LCDSetPixels = 0x20000007,
	
	/* Co-Processor addresses / commands */
	putByte = 0x30000000, // EXAMPLE
	getByte = 0x30000001, // EXAMPLE
};

volatile WORD * bus_address;
volatile WORD * bus_dataout;
volatile WORD * bus_datain;
volatile WORD * bus_ready;

/* Send action event at address. */
void action(WORD address);

/* Send data to address. */
void put(WORD address, WORD data);

/* Request data from address. Will block until data is ready. */
WORD get(WORD address);

/* Send data and request result through address. Will block until data is ready. */
WORD putget(WORD address, WORD data);

/* Read data from the bus, without request. Will block until data is ready. */
WORD read();

#endif /* DRIVER_H */

