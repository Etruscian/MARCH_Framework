/*
 * spi.cc
 *
 *  Created on: 15 Apr 2016
 *      Author: Projectmarch
 */

#include "spi.h"

void SPI::initializeSpi(u16 deviceID, u32 slaveMask){
	XSpi_Config* ConfigPtr;
	ConfigPtr = XSpi_LookupConfig(deviceID);
	XSpi_CfgInitialize(&spiDevice, ConfigPtr, ConfigPtr->BaseAddress);

	XSpi_SetOptions(&spiDevice, XSP_MASTER_OPTION | XSP_MANUAL_SSELECT_OPTION);

	XSpi_SetSlaveSelect(&spiDevice, slaveMask);
}

void SPI::setClockConfig(bool isActiveLow, bool isPhaseShifted){
	u32 optionsFlag = XSpi_GetOptions(&spiDevice);
	if (isActiveLow) optionsFlag |= XSP_CLK_ACTIVE_LOW_OPTION; else optionsFlag &= ~XSP_CLK_ACTIVE_LOW_OPTION;
	if (isPhaseShifted) optionsFlag |= XSP_CLK_PHASE_1_OPTION; else optionsFlag &= ~XSP_CLK_PHASE_1_OPTION;
	XSpi_SetOptions(&spiDevice, optionsFlag);
}

void SPI::enablePolled(void){
	XSpi_Start(&spiDevice);
	XSpi_IntrGlobalDisable(&spiDevice);
}

void SPI::initializeSlaveSelect(u16 deviceID){
	XGpio_Initialize(&slaveSelectDevice, deviceID);
	XGpio_DiscreteWrite(&slaveSelectDevice,1,0xFF);
}

void SPI::transfer(u8* MOSI, u8* MISO, u8 byteNum){
	XSpi_Transfer(&spiDevice,MOSI, MISO, byteNum);
}

void SPI::selectSlave(void){
	XGpio_DiscreteWrite(&slaveSelectDevice,1,0x00);
}

void SPI::deselectSlave(void){
	XGpio_DiscreteWrite(&slaveSelectDevice,1,0xFF);
}


// C interface
CSPI newCSPI(){
	return reinterpret_cast<void*>(new XSpi);
}

void delCSPI(void* cspi){
	delete reinterpret_cast<SPI*>(cspi);
}

void initializeCSpi(void* Cspi,u16 deviceID, u32 slaveMask){
	reinterpret_cast<SPI*>(Cspi)->initializeSpi(deviceID,slaveMask);
}

void setCClockConfig(void* Cspi,bool isActiveLow, bool isPhaseShifted){
	reinterpret_cast<SPI*>(Cspi)->setClockConfig(isActiveLow,isPhaseShifted);
}

void enableCPolled(void* Cspi){
	reinterpret_cast<SPI*>(Cspi)->enablePolled();
}

void transferC(void* Cspi,u8* MOSI, u8* MISO, u8 byteNum){
	reinterpret_cast<SPI*>(Cspi)->transfer(MOSI,MISO,byteNum);
}

void initializeCSlaveSelect(void* Cspi,u16 deviceID){
	reinterpret_cast<SPI*>(Cspi)->initializeSlaveSelect(deviceID);
}

void selectCSlave(void* Cspi){
	reinterpret_cast<SPI*>(Cspi)->selectSlave();
}

void deselectCSlave(void* Cspi){
	reinterpret_cast<SPI*>(Cspi)->deselectSlave();
}

