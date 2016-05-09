/*
 * rm08.cc
 *
 *  Created on: 15 Apr 2016
 *      Author: Projectmarch
 *
 *      This class incorporates all the implementations and bithandling
 *      necessary for the rm08 12 bit encoder aka motor encoder.
 */

#include "rm08.h"

#include <cstdio>

void rm08::initializeImpl() {
	spi.initializeSpi(MOTORENCODER_SPI_DEVICE_ID, DEFAULT_SLAVE_MASK);
	spi.setClockConfig(true, true);
	spi.enablePolled();
	ring_pos = 0;
}

void rm08::readImpl() {
	u16 enc_pos_prev;
	signed long int deltap;
	enc_pos_prev = angle;
	u8 MOSI = 0x00;
	u8 MISObuffer[2];

	// transfer garbage to sensor since it does not have a MOSI, receive sensor data 12 bit.
	spi.transfer(&MOSI, &MISObuffer[0], 2);

	// bitwise modify the buffers to accommodate for 12 bit int in 16 bit variable.
	MISObuffer[1] &= 0b01111111;
	angle = (((MISObuffer[1] << 5) + (MISObuffer[0] >> 3))<< 4); // shift 4 bits to the left for easier calculations

	// Calculate velocity from new position and stored positions.
	deltap = angle - enc_pos_prev;
	enc_filt += deltap - ring_ed[ring_pos];
	velocity = enc_filt >> 1;
	ring_ed[ring_pos] = deltap;
	ring_pos = (ring_pos+1) &0x1F;
}

int rm08::getAngleImpl() {
	return angle;
}

signed long int rm08::getVelocity() {

	return velocity;
}
