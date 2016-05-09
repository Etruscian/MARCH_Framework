/*
 * reporter.h
 *
 *  Created on: 18 Apr 2016
 *      Author: Projectmarch
 */

#include <exception>

#include "console.h"

class Reporter {
public:
	static void reportException(const std::exception &e);
};

inline void Reporter::reportException(const std::exception& e) {

	Console::writeLine(e.what());

}
