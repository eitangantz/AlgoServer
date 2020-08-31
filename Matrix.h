/*
 * Matrix.h
 *
 *  Created on: 18 Jan 2020
 *      Author: eitan
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include "Searchable.h"
#include "State.h"
#include <vector>
using namespace std;
class Matrix : public Searchable<pair<int,int>> {
private:
int N;
State<pair<int,int>>* source;
State<pair<int,int>>* destination;
vector<vector<int>> M;
public:
	Matrix(vector<vector<int>> m,State<pair<int,int>> *s,State<pair<int,int>> *d,int n) {
		M = m;
		source = s;
		destination = d;
		N = n;
	}
	virtual ~Matrix(){}
	State<pair<int,int>>* getInitialState() {
		return this->source;
	}
	State<pair<int,int>>* getGoalState(){
		return this->destination;
	}
	vector<State<pair<int,int>>*> getAllPossibleStates(State<pair<int,int>>* state) {
		vector<State<pair<int,int>>*> AllPossibleStates;
		int r = state->getStateRRepresentation().first;
		int c = state->getStateRRepresentation().second;
		int dr[] = {-1,1,0,0};
		int dc[] = {0,0,1,-1};
		int rr;
		int cc;
		for(int i = 0; i < 4; i++)
		{
			rr = r + dr[i];
			cc = c + dc[i];
			if ((rr<0) || (cc<0)) {continue;}
			if ((rr>=N) || (cc>=N)) {continue;}
			if (M[rr][cc] == -1) {continue;}
			pair<int,int> p(rr,cc);
			State<pair<int,int>>* newstate = new State<pair<int,int>>(p);
			newstate->setCameFrom(state);
			newstate->setCost(M[rr][cc]);
			newstate->setDistance(state->getDistance()+1);
			AllPossibleStates.push_back(newstate);
		}
		return AllPossibleStates;
	}
	string to_string() {
		string s = "";
        for(int i = 0;i<N;i++) {
            for(int j = 0; j<N;j++) {
                s += std::to_string(M[i][j]);
            }
        }
        return s;
	}
	string to_Hash_string() {
		string s = "";
        for(int i = 0;i<N;i++) {
            for(int j = (this->sumOfAll()+127+i*i)%N; j<N;j+= N/2 + i) {
                s += std::to_string(M[i][j]);
            }
        }
        return s;
	}
	int sumOfAll() {
		int sum = 0;
        for(int i = 0;i<N;i++) {
            for(int j = 0; j<N;j++) {
            	sum += M[i][j];
            }
        }
        return sum;
	}

	int getSizeOfSearchable() {
		return this->N;
	}
	vector<vector<int>> getStructure() {
		return this->M;
	}
	void setGoalState(State<pair<int,int>>* s) {
		this->destination = s;
	}
};


#endif /* MATRIX_H_ */
