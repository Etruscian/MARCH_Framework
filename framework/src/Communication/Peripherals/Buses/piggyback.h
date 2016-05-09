/*
 * piggyback.h
 *
 *  Created on: 19 Apr 2016
 *      Author: Projectmarch
 */

#ifndef PIGGYBACK_H_
#define PIGGYBACK_H_

#include <xil_types.h>

#include "../../../Services/SOES/soes.h"
#include "../bus.h"


class Piggyback : public Bus<Piggyback>
{
private:
	u32 Data;

public:
    Piggyback() {}
    ~Piggyback() {}

    inline void initializeImpl()
    {
    	soes_init();
    }

    inline void transferImpl()
    {

    }

    inline int getDataImpl()
    {
    	cb_get_Inputs();
    	return Data;
    }

    inline void setDataImpl(int data)
    {
    	cb_set_Outputs();
    }
};


#endif /* PIGGYBACK_H_ */
