/*
 * pwm.cc
 *
 *  Created on: 15 Apr 2016
 *      Author: Projectmarch
 */

#include "pwm.h"

// initializer
void PWM::initialize(u16 deviceID, u32 pwmFrequency) {
	this->pwmFrequency = pwmFrequency;				// save requested PWM frequency
	XTmrCtr_Initialize(&device, deviceID);			// initialize the device

	// Set the control/status register to allow PWM signal generation in both Timer 1 & 2 registers
	u32 pwmTCSR = XTC_CSR_ENABLE_PWM_MASK | XTC_CSR_DOWN_COUNT_MASK | XTC_CSR_EXT_GENERATE_MASK;
	XTmrCtr_SetControlStatusReg(device.BaseAddress,0,pwmTCSR);
	XTmrCtr_SetControlStatusReg(device.BaseAddress,1,pwmTCSR);

	// Configure PWM frequency in Timer 0 load register
	u32 TLR0 = device.Config.SysClockFreqHz/pwmFrequency-2;
	XTmrCtr_SetLoadReg(device.BaseAddress,0,TLR0);
}

// !!!! Would be better without float, directly giving TLR1, but then TLR0's max value should be known beforehand
void PWM::setDutyCycle(float duty) {
	//TEMPORARY maximize duty between up to 0.0.5
	//if (duty > 0.05) duty = 0.05;
	//END DEBUG CODE

	u32 TLR0 = XTmrCtr_GetLoadReg(device.BaseAddress,0);	// Read Timer 0 load register
	u32 TLR1 = (u32)(duty*(TLR0+2))-2;						// Calculate Timer 1 load register based on desired duty cycle
	XTmrCtr_SetLoadReg(device.BaseAddress,1,TLR1);			// Set Timer 1 load register
}

// enable/disable the counters to start PWM output generation
// might be better idea to do this through enable/disable of external signal generation bit
void PWM::enable() {
	// writing the enable all bit to any of the timer control/status registers
	// automatically enables both timers at the same time.
	u32 TCSR = XTmrCtr_GetControlStatusReg(device.BaseAddress,0);
	TCSR |= XTC_CSR_ENABLE_ALL_MASK;
	XTmrCtr_SetControlStatusReg(device.BaseAddress,0,TCSR);
}

void PWM::disable() {
	// disable both timers by setting their enable and enable all bits to 0
	// for PWM, both registers are the same so it's enough to work with one's value
	u32 TCSR = XTmrCtr_GetControlStatusReg(device.BaseAddress,0);
	TCSR &= ~(XTC_CSR_ENABLE_ALL_MASK | XTC_CSR_ENABLE_TMR_MASK);
	XTmrCtr_SetControlStatusReg(device.BaseAddress,0,TCSR);
	XTmrCtr_SetControlStatusReg(device.BaseAddress,1,TCSR);
}


