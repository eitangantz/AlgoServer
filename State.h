/*
 * State.h
 *
 *  Created on: 17 Jan 2020
 *      Author: eitan
 */

#ifndef STATE_H_
#define STATE_H_
using namespace std;
template<class T>
class State {
private:
int f;
int g;
int h;
T stateRepresentation;  //representation of the state.
int cost; //cost to reach this state.
State<T>* camefrom = NULL; //the state we came from to this state.
int distance; //for BFS -- distance from source to this state
bool visited = false;
public:
	State(T s) {
		this->stateRepresentation = s;
	}
	State() {

	}
	virtual ~State() {}
	void setCost(int cost1) {
		this->cost = cost1;
	}
	void setCameFrom(State<T> *camefrom1) {
		this->camefrom = camefrom1;
	}
	bool Equals(State<T> *s) {
		return (this->stateRepresentation == s->stateRepresentation);
	}
	void setDistance(int d) {
		this->distance = d;
	}
	T getStateRRepresentation() {
		return this->stateRepresentation;
	}
	int getDistance() {
		return this->distance;
	}
	bool getVisited() {
		return this->visited;
	}
	void setVisited() {
		this->visited = true;
	}
	State<T>*  getCameFrom() {
		return this->camefrom;
	}
	double getCost() {
		return this->cost;
	}
	void setF(int f1) {
		 f = f1;
	}
	void setG(int g1) {
		 g = g1;
	}
	void setH(int h1) {
		 h = h1;
	}
	int getF() {
		return this->f;
	}
	int getG() {
		return this->g;
	}
	int getH() {
		return this->h;
	}

};

#endif /* STATE_H_ */
