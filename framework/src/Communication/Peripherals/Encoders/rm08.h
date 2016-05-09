/*
 * rm08.h
 *
 *  Created on: 19 Apr 2016
 *      Author: Projectmarch
 */

#ifndef RM08_H_
#define RM08_H_

#include <xil_types.h>
#include <exception>

#include "../../../Config/device_defines.h"
#include "../../Drivers/spi.h"
#include "../encoder.h"

class rm08 : public Encoder<rm08>
{
private:
	SPI spi;
	u16 angle;
	u32 ring_pos;
	signed long int enc_filt,velocity,ring_ed[32];
public:
    rm08() {}
    ~rm08() {}

    // Implementations for template functions from encoder.h
    void initializeImpl();
    void readImpl();
    int getAngleImpl();
    signed long int getVelocity();

};


#endif /* RM08_H_ */
