/*
 * SOES Simple Open EtherCAT Slave
 *
 * File    : esc_hw.c
 * Version : 0.9.2
 * Date    : 22-02-2010
 * Copyright (C) 2007-2013 Arthur Ketels
 * Copyright (C) 2012-2013 rt-labs
 *
 * SOES is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation.
 *
 * SOES is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * As a special exception, if other files instantiate templates or use macros
 * or inline functions from this file, or you compile this file and link it
 * with other works to produce a work based on this file, this file does not
 * by itself cause the resulting work to be covered by the GNU General Public
 * License. However the source code for this file must still be made available
 * in accordance with section (3) of the GNU General Public License.
 *
 * This exception does not invalidate any other reasons why a work based on
 * this file might be covered by the GNU General Public License.
 *
 * The EtherCAT Technology, the trade name and logo "EtherCAT" are the intellectual
 * property of, and protected by Beckhoff Automation GmbH.
 */

/** \file
 * \brief
 * ESC hardware layer functions.
 *
 * Function to read and write commands to the ESC. Used to read/write ESC
 * registers and memory.
 */
#include "assert.h"
#include "utypes.h"
#include "esc.h"
#include <string.h>
#include "esc_hw.h"

#define ESC_CMD_READ    0x02
#define ESC_CMD_READWS  0x03
#define ESC_CMD_WRITE   0x04
#define ESC_CMD_NOP     0x00
#define ESC_TERM        0xff
#define ESC_NEXT        0x00
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
static uint8_t read_termination[MIN(sizeof(Wb), 128)] = { 0 };

void* spi;

static void esc_address(uint16_t address, uint8_t command, uint16_t * al_event) {
	/* Device is selected already.
	 * We use 2 bytes addressing.
	 */
	uint8_t data[2], Inbox[2];

	/* address 12:5 */
	data[0] = (address >> 5);
	/* address 4:0 and cmd 2:0 */
	data[1] = ((address & 0x1F) << 3) | command;

	/* Write (and read AL interrupt register) */
	transferC(spi, data, Inbox, sizeof(data));

	*((uint16_t*) al_event) = ((uint16_t) Inbox[1] << 8) | Inbox[0];
}

/** ESC read function used by the Slave stack.
 *
 * @param[in]   address     = address of ESC register to read
 * @param[out]  buf         = pointer to buffer to read in
 * @param[in]   len         = number of bytes to read
 * @param[out]  tALevent    = on every read we refresh the AL event register
 * @return 0 as default, the stack don't rely on any result
 */
uint16_t ESC_read(uint16_t address, void *buf, uint16_t len, void *tALevent) {
	/* Select device. */
	selectCSlave(spi);

	/* Write address and command to device. */
	esc_address(address, ESC_CMD_READ, (uint16_t *) tALevent);

	/* Here we want to read data and keep MOSI low (0x00) during
	 * all bytes except the last one where we want to pull it high (0xFF).
	 * Read (and write termination bytes).
	 */
	transferC(spi, read_termination + (sizeof(read_termination) - len),
			(uint8_t *) buf, len);
	/* Un-select device. */
	deselectCSlave(spi);
	/* result is never used */
	return 0;
}

/** ESC write function used by the Slave stack.
 *
 * @param[in]   address     = address of ESC register to write
 * @param[out]  buf         = pointer to buffer to write from
 * @param[in]   len         = number of bytes to write
 * @param[out]  tALevent    = on every read we refresh the AL event register
 * @return 0 as default, the stack don't rely on any result
 */
uint16_t ESC_write(uint16_t address, void *buf, uint16_t len, void *tALevent) {
	u8 dump[128];
	/* Select device. */
	selectCSlave(spi);
	/* Write address and command to device. */
	esc_address(address, ESC_CMD_WRITE, (uint16_t *) tALevent);
	/* Write data. */
	transferC(spi, (uint8_t *) buf, dump, len);
	/* Un-select device. */
	deselectCSlave(spi);
	/* result is never used */
	return 0;
}

void ESC_init(void) {
	read_termination[sizeof(read_termination) - 1] = 0xFF;
}
