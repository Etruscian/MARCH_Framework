/*
 * logic_dispatcher.h
 *
 *  Created on: 22 Apr 2016
 *      Author: Projectmarch
 */

#ifndef LOGIC_DISPATCHER_H_
#define LOGIC_DISPATCHER_H_

#include "../Controllers/motor_controller.h"

class DispatchLogic {
private:
	MotorControl motorController;
public:
	void initialize(void);
	void calculate(signed int velocitySetpoint, u16 motorAngle, signed long int motorVelocity, u32 jointAngle, u32 springAngle);
	void getData(float * anglePtr, float * magnitudePtr);
};

inline void DispatchLogic::initialize(void){
	motorController.initialize();
}

inline void DispatchLogic::calculate(signed int velocitySetpoint, u16 motorAngle, signed long int motorVelocity, u32 jointAngle, u32 springAngle){
	motorController.step(velocitySetpoint, motorAngle, motorVelocity, jointAngle, springAngle);
}

inline void DispatchLogic::getData(float* anglePtr, float * magnitudePtr){
	motorController.getData(anglePtr,magnitudePtr);
}

#endif /* LOGIC_DISPATCHER_H_ */
