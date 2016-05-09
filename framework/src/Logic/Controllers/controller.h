/*
 * controller.h
 *
 *  Created on: 26 Apr 2016
 *      Author: Daan
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <xil_types.h>
#include <vector>

template <class ControllerTemplate>
class Controller{
public:
    Controller()  { }
    ~Controller()  { }

    void initialize()
    {
      static_cast<ControllerTemplate*>(this)->initializeImpl();
    }

    void step(std::vector<u32>* dataIn, std::vector<u32>* dataOut){
    	static_cast<ControllerTemplate*>(this)->stepImpl(dataIn,dataOut);
    }
private:
};



#endif /* CONTROLLER_H_ */
