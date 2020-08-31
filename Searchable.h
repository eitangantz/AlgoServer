/*
 * Searchable.h
 *
 *  Created on: 17 Jan 2020
 *      Author: eitan
 */

#ifndef SEARCHABLE_H_
#define SEARCHABLE_H_
#include "State.h"
#include <list>
#include <vector>
using namespace std;
template<class T>
class Searchable {
public:
	Searchable() {}
	virtual ~Searchable() {}
	virtual State<T>* getInitialState() = 0;
	virtual State<T>* getGoalState() = 0;
	virtual vector<State<T>*> getAllPossibleStates(State<T>*) = 0;
	virtual int getSizeOfSearchable() = 0;
	virtual vector<vector<int>> getStructure() = 0;
	virtual void setGoalState(State<T>*) = 0;
	virtual string to_Hash_string() = 0;
	virtual int sumOfAll() = 0;

};

#endif /* SEARCHABLE_H_ */
