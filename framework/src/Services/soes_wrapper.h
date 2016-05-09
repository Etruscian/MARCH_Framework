/*
 * SOESWrapper.h
 *
 *  Created on: 28 Apr 2016
 *      Author: Projectmarch
 */

#ifndef SOESWRAPPER_H_
#define SOESWRAPPER_H_

#include "SOES/soes.h"

class SOESWrapper {
public:
	SOESWrapper();
	static void init();
	static void run();
	virtual ~SOESWrapper();
};

inline void SOESWrapper::init() {
	soes_init();
}

inline void SOESWrapper::run() {
	soes();
}

#endif /* SOESWRAPPER_H_ */
