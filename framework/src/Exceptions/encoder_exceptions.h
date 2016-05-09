/*
 * encoder_exceptions.h
 *
 *  Created on: 19 Apr 2016
 *      Author: Projectmarch
 */

#ifndef ENCODER_EXCEPTIONS_H_
#define ENCODER_EXCEPTIONS_H_

#include <stdexcept>

class EncoderException: public std::runtime_error {

public:
	EncoderException(std::string const& msg) :
			std::runtime_error(msg) {
	};

};



#endif /* ENCODER_EXCEPTIONS_H_ */
