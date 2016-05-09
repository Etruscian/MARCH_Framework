/*
 * aksim19.h
 *
 *  Created on: 19 Apr 2016
 *      Author: Projectmarch
 */

#ifndef AKSIM19_H_
#define AKSIM19_H_

#include <xil_types.h>
#include <exception>

#include "../../../Config/device_defines.h"
#include "../../Drivers/spi.h"
#include "../encoder.h"

class aksim19 : public Encoder<aksim19>
{
private:
	SPI spi;
	u32 angle;
  public:
    aksim19() {  }
    ~aksim19() {  }

    // Implementations for template functions from encoder.h
    void initializeImpl();
    void readImpl();
    int getAngleImpl();

};

#endif /* AKSIM19_H_ */
