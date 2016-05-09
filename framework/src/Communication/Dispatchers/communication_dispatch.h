/*
 * communication_dispatch.h
 *
 *  Created on: 19 Apr 2016
 *      Author: Projectmarch
 */

#ifndef COMMUNICATION_DISPATCH_H_
#define COMMUNICATION_DISPATCH_H_

#include <xil_types.h>
#include <vector>

#include "../Peripherals/Buses/piggyback.h"
#include "../Peripherals/Encoders/aksim19.h"
#include "../Peripherals/Encoders/aksim20.h"
#include "../Peripherals/Encoders/rm08.h"
#include "../Peripherals/MotorDrives/motor_drive.h"

class DispatchCommunication {
private:
	rm08 motorEncoder;
	aksim19 jointEncoder;
	aksim20 springEncoder;
	Piggyback piggyback;
	MotorDrive motorDrive;
public:
	void initialize();
	void getData(u16*,signed int*,u32*,u32*);
	std::vector<u32> getDataVector(std::vector<std::reference_wrapper<Peripheral>>);
	void setMotorDriveSetpoint(float angle, float magnitude);
};


#endif /* COMMUNICATION_DISPATCH_H_ */
