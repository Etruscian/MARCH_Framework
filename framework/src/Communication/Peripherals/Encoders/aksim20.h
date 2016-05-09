/*
 * aksim20.h
 *
 *  Created on: 19 Apr 2016
 *      Author: Projectmarch
 */

#ifndef AKSIM20_H_
#define AKSIM20_H_

#include <xil_types.h>
#include <exception>

#include "../../../Config/device_defines.h"
#include "../../Drivers/spi.h"
#include "../encoder.h"

class aksim20 : public Encoder<aksim20>
{
private:
	SPI spi;
	u32 angle;
  public:
    aksim20() {  }
    ~aksim20() {  }

    // Implementations of template functions from encoder.h
    void initializeImpl();
    void readImpl();
    int getAngleImpl();
};



#endif /* AKSIM20_H_ */
