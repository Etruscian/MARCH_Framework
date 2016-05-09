/*
 * motor_controller.h
 *
 *  Created on: 26 Apr 2016
 *      Author: Daan
 */

#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_

#include <xil_types.h>
#include <vector>

#include "../controller.h"

class MotorController : public Controller<MotorController> {
private:
	std::vector<u32> dataIn, dataOut;
public:
	void initializeImpl();
	void stepImpl(std::vector<u32>*, std::vector<u32>*);
};

inline void MotorController::initializeImpl(){

}

inline void MotorController::stepImpl(std::vector<u32>* dataInPtr,std::vector<u32>* dataOutPtr){
	dataIn = *dataInPtr;

	// perform logic step
	// dataOut = logicLoopstep()

	dataOutPtr = &dataOut;
}



#endif /* MOTOR_CONTROLLER_H_ */
