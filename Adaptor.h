/*
 * Adaptor.h
 *
 *  Created on: 17 Jan 2020
 *      Author: eitan
 */

#ifndef ADAPTOR_H_
#define ADAPTOR_H_
#include "Solver.h"
#include "Isearcher.h"
#include "Searchable.h"
template<class P, class S, class T>
class Adaptor : public Solver<P,S>{
private:
Isearcher<S,T>* searcher;
public:
	Adaptor(Isearcher<S,T>* ALgo){
		searcher = ALgo;
	}
	virtual ~Adaptor(){}
	S slove(P searchable){
		return searcher->search(searchable);
	}

};

#endif
