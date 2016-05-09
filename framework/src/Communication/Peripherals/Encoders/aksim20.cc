/*
 * aksim20.cc
 *
 *  Created on: 15 Apr 2016
 *      Author: Projectmarch
 *
 *      This class incorporates all the implementations and bithandling
 *      necessary for the Aksim 20 bit encoder aka spring encoder.
 */

#include "aksim20.h"

#include <cstdio>

void aksim20::initializeImpl() {
	spi.initializeSpi(SPRINGENCODER_SPI_DEVICE_ID, DEFAULT_SLAVE_MASK);
	spi.setClockConfig(true, true);
	spi.enablePolled();
}

void aksim20::readImpl() {
	u8 MOSI = 0x00;
	u8 MISObuffer[4];
	spi.transfer(&MOSI, &MISObuffer[0], 4);
	angle = ((MISObuffer[0] >> 5) | (MISObuffer[1] << 3) | (MISObuffer[3] << 11));

}

int aksim20::getAngleImpl() {
	return angle;
}
