/*
 * console.cc
 *
 *  Created on: 18 Apr 2016
 *      Author: Projectmarch
 */

#include <xil_types.h>
#include <cstdio>

//#include <string>

/**
 * This class is meant to make writing to console easier. We should implement a nice wrapper first of all to write new lines
 * but also a way to print tables and so on.
 */

class Console {
public:
	static void writeLine(const char8* str);
	static void writeLine(const u64);
	static void writeLine(const u32);
	static void writeLine(const u16);
};

/**
 * @todo move implementation
 */
inline void Console::writeLine(const char8* str) {
	printf("%s\n", str);
}

inline void Console::writeLine(const u64 integer){
	printf("%llu\n",integer);
}

inline void Console::writeLine(const u32 integer){
	printf("%lu\n",integer);
}

inline void Console::writeLine(const u16 integer){
	printf("%u\n",integer);
}
