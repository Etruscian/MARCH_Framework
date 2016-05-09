/*
 * Empty C++ Application
 */

#include <xil_exception.h>
#include <xil_io.h>
#include <xscugic.h>
#include <xscutimer.h>
#include <cstdio>
#include <exception>

#include "Config/timer_defines.h"
#include "platform.h"
#include "Services/reporter.h"
#include "Services/supervisor.h"
#include "Services/SOES/soes.h"

//#include "Services/timer.h"

Supervisor supervisor;
XScuTimer TimerInstance;
XScuGic IntcInstance;

void interruptRoutine(void *CallBackRef) {
	// Define pointer to timer
	XScuTimer *TimerInstancePtr = (XScuTimer *) CallBackRef;

	// If timer is expired, clear interrupt status
	if (XScuTimer_IsExpired(TimerInstancePtr)) {
		XScuTimer_ClearInterruptStatus(TimerInstancePtr);

		// Main loop
		supervisor.run();

	}
}

void initInterrupt(void) {
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
	XScuTimer_LoadTimer(&TimerInstance, TIMER_LOAD_VALUE_20KHZ);

	// Start interrupt
	XScuTimer_Start(&TimerInstance);
}

int init() {

	initInterrupt();
	printf("Interrupt initialized\n");
	supervisor.initialize();
	printf("Supervisor initialized\n");

	return 0;
}

int main() {
	// Do not remove
	init_platform();


	try {
		init();
	} catch (const std::exception &e) {

		Reporter::reportException(e);

	}
	while (true) {
		soes();
	}

	// Do not remove
	cleanup_platform();

	return 0;
}
