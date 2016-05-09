/*
 * DriverExceptions.h
 *
 *  Created on: 18 Apr 2016
 *      Author: Projectmarch
 */

#ifndef DRIVEREXCEPTIONS_H_
#define DRIVEREXCEPTIONS_H_

#include <iostream>
#include <stdexcept>

class SPIException: public std::runtime_error {

public:
	SPIException(std::string const& msg) :
			std::runtime_error(msg) {
	};

};

class UARTException: public std::runtime_error {
public:
	UARTException(std::string const& msg) :
			std::runtime_error(msg) {

	}
};

#endif /* DRIVEREXCEPTIONS_H_ */
