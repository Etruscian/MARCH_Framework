/*
 * motor_drive.h
 *
 *  Created on: 2 May 2016
 *      Author: Projectmarch
 */

#ifndef MOTOR_DRIVE_H_
#define MOTOR_DRIVE_H_

#include <sleep.h>
#include <xgpio.h>
#include <xil_types.h>
#include <cstdio>

#include "../../../Config/device_defines.h"
#include "../../Drivers/pwm.h"

#define WRITECMD		0x0
#define READCMD			0x1

#define STATREG1ADDR	0x0
#define StATREG2ADDR	0x1

#define CTRLREG1ADDR	0x2
#define CTRLREG2ADDR	0x3

#define PWM3MODE		0x08

#define PWM_LIMIT  		   	(float)(4500 * 0.98)

class MotorDrive{
private:
	XGpio motorEnable;
	PWM pwm_u,pwm_v, pwm_w;
	SPI spi;
	float getPwmTab(float angle);
	void calculateDutyCycles(float angle, float magnitude, float * dutyCycleU, float * dutyCycleV, float * dutyCycleW);
	float max(float x,float y);
public:
	void initialize(void);
	void setMotorEnable(void);
	void setPwmDutyCycles(float angle, float magnitude);
};


// PRIVATE FUNCTIONS

inline float MotorDrive::max(float x,float y){
	return (x<y) ? x : y;
}
/*	Shifts the angle by 30 degrees and makes it cyclic.
 *	Returns a value between 0 and 1 based on the shifted angle.
 */
inline float MotorDrive::getPwmTab(float angle){
	angle = angle + 30;   //shift +30 degrees for easier equations
	angle = angle - 360*((u32)(angle/360));	// make angle between 0 and 360 again, but shifted

	if (angle < 60) {
		return angle/60;
	} else if (angle < 180) {
		return 1;
	} else if (angle < 240) {
		return (240-angle)/60;
	} else {
		return 0;
	}
}

/*	Calculates the duty cycles of each pwm generator in order to reach the given angle.
 *	It uses the function getPwmTab, which shifts the angle 30 degrees, makes it cyclic and
 *	returns a value between 0 and 1 based on the shifted angle.
 *	Output is stored in the last 3 arguments.
 */ 
inline void MotorDrive::calculateDutyCycles(float angle, float magnitude, float * dutyCycleU, float * dutyCycleV, float * dutyCycleW){

	*((float *) dutyCycleU) = max(0.1+magnitude*getPwmTab(angle),PWM_LIMIT);
	*((float *) dutyCycleV) = max(0.1+magnitude*getPwmTab(angle+240),PWM_LIMIT);
	*((float *) dutyCycleW) = max(0.1+magnitude*getPwmTab(angle+120),PWM_LIMIT);

}
// PUBLIC FUNCTIONS

/* Initializes the motor drive by initializing the pwm generators and finally initializing
 * the motor enable GPIO pin. Writes this pin to low to prevent the motor from enabling.
 */
inline void MotorDrive::initialize(void){
	pwm_u.initialize(MOTOR_PWM_U_ID, MOTOR_PWM_FREQUENCY);
	pwm_v.initialize(MOTOR_PWM_V_ID, MOTOR_PWM_FREQUENCY);
	pwm_w.initialize(MOTOR_PWM_W_ID, MOTOR_PWM_FREQUENCY);

	spi.initializeSpi(MOTORDRIVE_SPI_DEVICE_ID, DEFAULT_SLAVE_MASK);
	spi.setClockConfig(false,true);
	spi.enablePolled();

	u8 MOSI[2],MISO[2];
	u16 data;
	data = (PWM3MODE | (14<<6));
	MOSI[0] = (0 << 7) | (0x02<<3) | (data >> 8);
	MOSI[1] = data & 0xFF;

	spi.transfer(&MOSI[0],&MOSI[0],2);
	spi.transfer(&MISO[0],&MISO[0],2);

	MOSI[0] = (1<<7) | (0x02 << 3);
	MOSI[1] = 0;

	spi.transfer(&MOSI[0],&MOSI[0],2);
	spi.transfer(&MISO[0],&MISO[0],2);

	XGpio_Initialize(&motorEnable,MOTORENABLE_GPIO_DEVICE_ID);
	XGpio_DiscreteWrite(&motorEnable,1,0x00);
}

/* Enables pwm generators and sets the motor enable GPIO pin to high.
 */
inline void MotorDrive::setMotorEnable(void){
	pwm_u.setDutyCycle(0.01f);
	pwm_v.setDutyCycle(0.01f);
	pwm_w.setDutyCycle(0.01f);
	pwm_u.enable();
	pwm_v.enable();
	pwm_w.enable();

	XGpio_DiscreteWrite(&motorEnable,1,0xFF);
}

/* Sets the duty cycles of the pwm generators based on the angle and magnitude passed down
 * from the Dispatcher. 
 * Uses private function calculateDutyCycles to calculate the duty cycles for each generator.
 */
inline void MotorDrive::setPwmDutyCycles(float angle, float magnitude){
	float dutyU, dutyV, dutyW;
	//angle = 30;
	//magnitude = 2;
	calculateDutyCycles(angle,magnitude,&dutyU,&dutyV,&dutyW);
//	printf("%f %f %f %f %f\n",angle, magnitude,dutyU,dutyV,dutyW);
	pwm_u.setDutyCycle(dutyU);
	pwm_v.setDutyCycle(dutyV);
	pwm_w.setDutyCycle(dutyW);
}

#endif /* MOTOR_DRIVE_H_ */
