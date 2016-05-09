/*
 * supervisor.h
 *
 *  Created on: 6 May 2016
 *      Author: Sander
 */

#ifndef SUPERVISOR_H_
#define SUPERVISOR_H_

#include <xil_types.h>
#include <cstdio>

#include "../Communication/Dispatchers/communication_dispatch.h"
#include "../Logic/Dispatchers/logic_dispatcher.h"

class Supervisor{
private:
	DispatchCommunication dispatchComm;
	DispatchLogic dispatchLogic;
	u16 motorAngle;
	u32 jointAngle, springAngle;
	signed int motorVelocity;
	signed int velocitySetpoint;
	float angle,magnitude;
public:
	void initialize(void);
	void run(void);
};

inline void Supervisor::initialize(void){
	dispatchComm.initialize();
	printf("Communication initialized\n");
	dispatchLogic.initialize();
	printf("Logic initialized\n");
	velocitySetpoint = 30;
}

inline void Supervisor::run(void){
	dispatchComm.getData(&motorAngle, &motorVelocity, &jointAngle, &springAngle);
	dispatchLogic.calculate(velocitySetpoint,motorAngle,motorVelocity,jointAngle,springAngle);
	dispatchLogic.getData(&angle,&magnitude);
	dispatchComm.setMotorDriveSetpoint(angle,magnitude);
}

#endif /* SUPERVISOR_H_ */
