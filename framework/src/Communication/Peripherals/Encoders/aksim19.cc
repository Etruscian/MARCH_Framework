/*
 * aksim19.cc
 *
 *  Created on: 15 Apr 2016
 *      Author: Projectmarch
 *
 *      This class incorporates all the implementations and bithandling
 *      necessary for the Aksim 19 bit encoder aka joint encoder.
 */

#include "aksim19.h"

#include <cstdio>

    //here comes the implementation of the write method on the subclass
void aksim19::initializeImpl()
    {
		spi.initializeSpi(JOINTENCODER_SPI_DEVICE_ID, DEFAULT_SLAVE_MASK);
		spi.setClockConfig(true, true);
		spi.enablePolled();
    }

void aksim19::readImpl()
    {
		u8 MOSI = 0x00;
		u8 MISObuffer[4];
		spi.transfer(&MOSI, &MISObuffer[0],4);
		angle = (((MISObuffer[3] )<<11) + (MISObuffer[2]<<3) + (MISObuffer[1] >> 5 ));
    }

int aksim19::getAngleImpl()
    {
    	return angle;
    }
