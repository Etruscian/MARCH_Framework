/*
 * spi.h
 *
 *  Created on: 19 Apr 2016
 *      Author: Projectmarch
 */

#ifndef SPI_H_
#define SPI_H_

#include "xgpio.h"
#include <xspi.h>

class SPI{
private:
	XSpi spiDevice;
	XGpio slaveSelectDevice;

public:
	void initializeSpi(u16 deviceID, u32 slaveMask);
	void setClockConfig(bool isActiveLow, bool isPhaseShifted);
	void enablePolled(void);
	void initializeSlaveSelect(u16 deviceID);
	void transfer(u8* MOSI, u8* MISO, u8 byteNum);
	void selectSlave(void);
	void deselectSlave(void);
};

// C interface
typedef void* CSPI;

extern "C" CSPI newCSPI();
extern "C" void delCSPI(CSPI);

extern "C" void initializeCSpi(CSPI,u16 deviceID, u32 slaveMask);
extern "C" void setCClockConfig(CSPI,bool isActiveLow, bool isPhaseShifted);
extern "C" void enableCPolled(CSPI);
extern "C" void initializeCSlaveSelect(CSPI,u16 deviceID);
extern "C" void transferC(CSPI,u8* MOSI, u8* MISO, u8 byteNum);
extern "C" void selectCSlave(CSPI);
extern "C" void deselectCSlave(CSPI);


#endif /* SPI_H_ */
