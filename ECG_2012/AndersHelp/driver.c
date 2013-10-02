#include "config.h"
#include "driver.h"
#ifdef DEBUG_DRIVER
#ifdef DEBUG_ARM
#include <stdio.h>
#endif /* DEBUG_ARM */
#endif /* DEBUG_DRIVER */

/* Memory mapped access to the bus */
volatile WORD * bus_address = (volatile WORD *) 0x80000000;
volatile WORD * bus_dataout = (volatile WORD *) 0x80000004;
volatile WORD * bus_datain  = (volatile WORD *) 0x80000008;
volatile WORD * bus_ready   = (volatile WORD *) 0x8000000C;

void action(WORD address) {
#ifdef DEBUG_DRIVER
#ifdef DEBUG_ARM
	printf("void action(%X)\n", address);
	fflush(stdout);
#endif /* DEBUG_ARM */
#endif /* DEBUG_DRIVER */
	*bus_address = address;
}

void put(WORD address, WORD data) {
#ifdef DEBUG_DRIVER
#ifdef DEBUG_ARM
	printf("void put(%X, %X)\n", address, data);
	fflush(stdout);
#endif /* DEBUG_ARM */
#endif /* DEBUG_DRIVER */
	// Always write data first
	*bus_dataout = data;
	*bus_address = address;
}

WORD get(WORD address) {
#ifdef DEBUG_DRIVER
#ifdef DEBUG_ARM
	printf("WORD get(%X)\n", address);
	fflush(stdout);
#endif /* DEBUG_ARM */
#endif /* DEBUG_DRIVER */
	*bus_address = address;
	// Wait for slave to respond
	while (*bus_ready != 1);
	return *bus_datain;
}

WORD putget(WORD address, WORD data) {
#ifdef DEBUG_DRIVER
#ifdef DEBUG_ARM
	printf("WORD putget(%X, %X)\n", address, data);
	fflush(stdout);
#endif /* DEBUG_ARM */
#endif /* DEBUG_DRIVER */
	// Always write data first
	*bus_dataout = data;
	*bus_address = address;
	// Wait for slave to respond
	while (*bus_ready != 1);
	return *bus_datain;
}

WORD read() {
#ifdef DEBUG_DRIVER
#ifdef DEBUG_ARM
	printf("WORD read()\n");
	fflush(stdout);
#endif /* DEBUG_ARM */
#endif /* DEBUG_DRIVER */
	// Wait for slave to respond
	while (*bus_ready != 1);
	return *bus_datain;
}
