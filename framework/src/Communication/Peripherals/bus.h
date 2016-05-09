/*
 * bus.h
 *
 *  Created on: 15 Apr 2016
 *      Author: Projectmarch
 */

#ifndef BUS_H_
#define BUS_H_

#include "../../Config/device_defines.h"
#include "../../Exceptions/encoder_exceptions.h"

template<class Template>
class Bus {

public:
	Bus() {
	}
	~Bus() {
	}

	void initialize() {
		static_cast<Template*>(this)->initializeImpl();
	}

	void transfer() {
		static_cast<Template*>(this)->transferImpl();
	}

	int getData() {
		static_cast<Template*>(this)->getDataImpl();
	}

	void setData(int) {
		static_cast<Template*>(this)->setDataImpl();
	}
};

#endif /* BUS_H_ */
