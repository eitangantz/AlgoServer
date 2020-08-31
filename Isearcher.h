/*
 * Isearcher.h
 *
 *  Created on: 17 Jan 2020
 *      Author: eitan
 */

#ifndef ISEARCHER_H_
#define ISEARCHER_H_
#include "Searchable.h"
template<class S, class T>
class Isearcher {
public:
	Isearcher(){}
	virtual ~Isearcher(){}
    virtual S search(Searchable<T>* searchable) = 0;
    virtual int getNumberOfNodesEvaluate() = 0;
};

#endif /* SEARCHER_H_ */
