/*
 * motor_controller.h
 *
 *  Created on: 2 May 2016
 *      Author: Projectmarch
 */

#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_

#include <xil_types.h>
#include <cstdint>

#include "../../Communication/Peripherals/MotorDrives/motor_drive.h"

#define POLEPAIRS			14
#define ENCMAX 				65536// (max 16 bits value, since encoder is bitshifted << 4)
#define C_VELOCITY_P 		(signed int)175
#define TORQUE_LIMIT	  	(signed int)32767
#define C_LAG				(int16_t)(ENCMAX/2 * 0.206)
#define C_TORQUE	       	(int16_t)(ENCMAX/2 * 0.030517)
#define C_VELOCITY         	(int16_t)(ENCMAX/2 * 0.138)
#define DEFAULTPHASESHIFT  	(uint16_t)(23360) // (90 or 128 degrees, angle at which torque is exerted)
#define PHASEOFFSET			(uint16_t)(3000)// (difference between electrical position and encoder position)

#define ANGLE_45    (uint16_t)(ENCMAX *  45 / 360)
#define ANGLE_180   (uint16_t)(ENCMAX *  180 / 360)

class MotorControl{
private:
	int startupcount;
	float angle, magnitude;
	signed int angleCalc,amplitude;
	signed int clip_s(signed int,signed int);

public:
	void initialize(void);
	void step(signed int velocitySetpoint, u16 motorAngle, signed int motorVelocity, u32 jointAngle, u32 springAngle);
	void getData(float * anglePtr, float * magnitudePtr);
};

inline void MotorControl::initialize(void){
	startupcount = 256;
	angleCalc = 0;
	amplitude = 0;
}

inline signed int MotorControl::clip_s(signed int val, signed int minmax) {
	if (val > minmax)
		return minmax;
	else if (val <-minmax){
		minmax = -minmax;
		return minmax;}
	else
		return val;
}

inline void MotorControl::step(signed int velocitySetpoint, u16 motorAngle, signed int motorVelocity, u32 jointAngle, u32 springAngle){
	uint16_t encoderElectric;
	signed int torquereq;
	signed int lag_compensation;
	int16_t phase;

	// calculate electrical degrees
	encoderElectric = (uint16_t) (((uint32_t) (motorAngle) * POLEPAIRS ) % ENCMAX);
	torquereq = (signed int) clip_s((velocitySetpoint - motorVelocity) * C_VELOCITY_P, TORQUE_LIMIT);
	if (startupcount) {
		startupcount--;
	} else {
		//calculate required amplitude
		amplitude = ((torquereq * C_TORQUE ) >> 15)	+ ((motorVelocity * C_VELOCITY ) >> 12);
		lag_compensation = clip_s((motorVelocity * C_LAG ) >> 12, ANGLE_45);
		if (lag_compensation < 0)
			lag_compensation = -lag_compensation;
		phase = DEFAULTPHASESHIFT;

		if (amplitude < 0) {
			amplitude = -amplitude;
			phase += ANGLE_180;
			lag_compensation = -lag_compensation;
		}
		if (amplitude > PWM_LIMIT)
			amplitude = PWM_LIMIT;
		angleCalc = encoderElectric + phase + lag_compensation;
	}


	// angleCalc is from 0 - 65536 (4096 bitshifted left by 4) === 0 -> 360 degrees, amplitude is from 0 - 5000
	// convert to our representation of angle 0-360 float, magnitude 0 - 1
	angle = (float) (angleCalc) * 360 / ENCMAX;
	magnitude = (float) (amplitude) / 5000;
}

inline void MotorControl::getData(float * anglePtr, float * magnitudePtr){
	*((float * ) anglePtr) = angle;
	*((float * ) magnitudePtr) = magnitude;
}


#endif /* MOTOR_CONTROLLER_H_ */
