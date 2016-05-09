/*
 * usb.h
 *
 *  Created on: 26 Apr 2016
 *      Author: Daan
 */

#ifndef USB_H_
#define USB_H_

#include <xil_types.h>
#include <xparameters.h>

#include "../bus.h"
#include "xuartps_hw.h"


class Usb : public Bus<Usb>
{
private:
	u32 baseAddress;

public:
    Usb() {}
    ~Usb() {}

    void initializeImpl();
    void readImpl(u32*);
    void sendByte(u32*);
    int dataReady();

};
    inline void Usb::initializeImpl()
    {
    	this->baseAddress = STDIN_BASEADDRESS;
    }

    inline void Usb::readImpl(u32* data){
    	u32 RecievedByte = XUartPs_ReadReg(STDIN_BASEADDRESS, XUARTPS_FIFO_OFFSET);
    	data = &RecievedByte;
    }

    inline void Usb::sendByte(u32* byte){
    	XUartPs_SendByte(STDOUT_BASEADDRESS, *byte);
    }

    inline int Usb::dataReady(){
    	if (XUartPs_IsReceiveData(STDIN_BASEADDRESS)){
    			return 1;
    		}
    		else{
    			return 0;
    		}
    }



#endif /* USB_H_ */
