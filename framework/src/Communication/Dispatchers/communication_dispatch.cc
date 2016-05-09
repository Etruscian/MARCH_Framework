/*
 * communication_dispatch.cc
 *
 *  Created on: 19 Apr 2016
 *      Author: Projectmarch
 */

#include "communication_dispatch.h"


void DispatchCommunication::initialize() {
	// Encoders
	motorEncoder.initialize();
	jointEncoder.initialize();
	springEncoder.initialize();
//
//	// Bus link
	piggyback.initialize();
//
//	// Motor Drive
	motorDrive.initialize();
	motorDrive.setMotorEnable();
}

void DispatchCommunication::getData(u16* motorAngle,signed int* motorVelocity, u32* jointAngle, u32* springAngle) {
	motorEncoder.read();
	jointEncoder.read();
	springEncoder.read();
	*((u16*) motorAngle) = motorEncoder.getAngle();
	*((signed long int*) motorVelocity) = motorEncoder.getVelocity();
	*((u32*) jointAngle) = jointEncoder.getAngle();
	*((u32*) springAngle) = springEncoder.getAngle();
}

std::vector<u32> DispatchCommunication::getDataVector(std::vector<std::reference_wrapper<Peripheral>> peripherals) {
 // WIP
	std::vector<u32> dataVector;
	return dataVector;
}

void DispatchCommunication::setMotorDriveSetpoint(float angle, float magnitude){
	motorDrive.setPwmDutyCycles(angle,magnitude);

}
