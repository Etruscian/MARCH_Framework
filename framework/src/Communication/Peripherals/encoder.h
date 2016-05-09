/*
 * encoder.cc
 *
 *  Created on: 15 Apr 2016
 *      Author: Projectmarch
 */

#ifndef ENCODER_H
#define ENCODER_H

#include "peripheral.h"


template <class Template>

/**
 * The encoder class extends from peripheral so the delegator can call for a vector of all peripherals
 */
class Encoder : public Peripheral
{
  public:
    Encoder()  { }
    ~Encoder()  { }

    void initialize()
    {
      static_cast<Template*>(this)->initializeImpl();
    }

    void read(){
    	static_cast<Template*>(this)->readImpl();
    }

    int getAngle(){
    	static_cast<Template*>(this)->getAngleImpl();
    }
};

#endif



