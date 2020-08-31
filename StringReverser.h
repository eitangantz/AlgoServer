/*
 * StringReverser.h
 *
 *  Created on: 15 Jan 2020
 *      Author: eitan
 */

#ifndef STRINGREVERSER_H_
#define STRINGREVERSER_H_
#include "Solver.h"
#include <string>
using namespace std;
class StringReverser : public Solver<string,string>{
public:
	StringReverser() {}
	virtual ~StringReverser() {}
	string slove(string problem);

};

#endif /* STRINGREVERSER_H_ */
