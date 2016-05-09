/*
 * pwm.h
 *
 *  Created on: 2 May 2016
 *      Author: Projectmarch
 */

#ifndef PWM_H_
#define PWM_H_

#include <xil_types.h>
#include "xtmrctr.h"
#include "../../Config/device_defines.h"

class PWM {
private:
	XTmrCtr device;
	u32 pwmFrequency;

public:
	void initialize(u16 deviceID, u32 pwmFrequency);
	void enable();
	void disable();
	void setDutyCycle(float duty);
};



#endif /* PWM_H_ */
