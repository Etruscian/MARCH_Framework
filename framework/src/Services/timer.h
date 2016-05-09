/*
 * timer.cc
 *
 *  Created on: 15 Apr 2016
 *      Author: Projectmarch
 */

#include <sleep.h>
#include <xil_exception.h>
#include <xil_io.h>
#include <xil_types.h>
#include <xscugic.h>
#include <xscutimer.h>
#include <xtime_l.h>

#include "../Config/timer_defines.h"

//#include "console.h"

//#include "inttypes.h"

XScuTimer TimerInstance;
XScuGic IntcInstance;

class Timer {
private:

public:

	/**
	 * Method prototypes
	 */
	static void initInterrupt(void);
	static void interruptRoutine(void*);
	static void wait(u32 seconds);
	static void startClockCycle(void);
	static void finishClockCycle(void);
	static void setFrequency(u32 frequency);
	static void run();

	/**
	 * Class fields
	 */
	static u32 frequency;
	static u64 startTime, stopTime, currentTime;

};

/**
 * Method implementations
 */

/**
 * Initialize main interrupt routine
 */
inline void Timer::initInterrupt(void) {
	// Declare pointers
	XScuTimer_Config* ConfigPtr;
	XScuGic_Config* IntcConfig;

	// Initialize timers by looking up config and initializing with that config
	ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
	XScuTimer_CfgInitialize(&TimerInstance, ConfigPtr, ConfigPtr->BaseAddr);
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	XScuGic_CfgInitialize(&IntcInstance, IntcConfig,
			IntcConfig->CpuBaseAddress);

	// Initialize exception handling
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
			(Xil_ExceptionHandler) XScuGic_InterruptHandler, &IntcInstance);

	// Connect interrupt routine to exception handler
	XScuGic_Connect(&IntcInstance, TIMER_IRPT_INTR,
			(Xil_ExceptionHandler) interruptRoutine, (void *) (&TimerInstance));

	// Enable interrupts
	XScuGic_Enable(&IntcInstance, TIMER_IRPT_INTR);
	XScuTimer_EnableInterrupt(&TimerInstance);

	// Enable exception handler
	Xil_ExceptionEnable();

	// Set auto reload so timer reloads when interrupt is cleared
	XScuTimer_EnableAutoReload(&TimerInstance);

	// Set timer value
	XScuTimer_LoadTimer(&TimerInstance, TIMER_LOAD_VALUE);

	// Start interrupt
	XScuTimer_Start (&TimerInstance);
}

/**
 * main interrupt routine
 */
inline void Timer::interruptRoutine(void *CallBackRef) {
	// Define pointer to timer
	XScuTimer *TimerInstancePtr = (XScuTimer *) CallBackRef;

	// If timer is expired, clear interrupt status
	if (XScuTimer_IsExpired(TimerInstancePtr)) {
		XScuTimer_ClearInterruptStatus(TimerInstancePtr);

		// Run the main application loop
		printf("test\n");

		// run function in main
	}
}

inline void Timer::setFrequency(u32 seconds) {
	Timer::frequency = seconds;
}

/**
 * Get the current time and save it for later calculation
 */
inline void Timer::startClockCycle(void) {
	XTime startTime;
	XTime_GetTime(&startTime);
	Timer::startTime = (u64) startTime;

}

/**
 * Calculate how many seconds we have to wait based on the frequency we are sampling at and the time the calculation took
 */
inline void Timer::finishClockCycle(void) {
	XTime currentTime;
	XTime_GetTime(&currentTime);

	// calculate how many ticks we have left until the next refresh
	// wait that amount of ticks

}

inline void Timer::wait(u32 seconds) {
	sleep(seconds);
}

inline void Timer::run(){

}

