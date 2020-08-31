/*
 * Solver.h
 *
 *  Created on: 13 Jan 2020
 *      Author: eitan
 */

#ifndef SOLVER_H_
#define SOLVER_H_
template<class P, class S>
class Solver {
public:
	Solver(){}
	virtual ~Solver(){}
	virtual S slove(P problem) = 0;
};

#endif /* SOLVER_H_ */
