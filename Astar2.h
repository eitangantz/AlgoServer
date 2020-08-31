/*
 * Astar2.h
 *
 *  Created on: 21 Jan 2020
 *      Author: eitan
 */

#ifndef ASTAR2_H_
#define ASTAR2_H_
#include <string>
#include "Isearcher.h"
#include "Searchable.h"
#include <queue>
#include <algorithm>
#include <set>
#include "algorithm"
#include <list>
#include "State.h"
#include <mutex>          // std::mutex


class Astar2 :public Isearcher<string,pair<int,int>>{
private:
State<pair<int,int>>* startNode;
State<pair<int,int>>* endNode;
int	evaluatedNodes = 0;
vector<State<pair<int,int>>*> open;
vector<State<pair<int,int>>*> closed;
Searchable<pair<int,int>>* searchable1;
std::mutex mtx;
public:
	Astar2(){}
	virtual ~Astar2(){}
    string search(Searchable<pair<int,int>>* searchable) {
    	mtx.lock();
				open.clear();
				closed.clear();
				evaluatedNodes = 0;
    			this->searchable1 = searchable;
    			pair<int,int> startPair(searchable->getInitialState()->getStateRRepresentation().first,searchable->getInitialState()->getStateRRepresentation().second);
    			startNode = new State<pair<int,int>>(startPair);
    			pair<int,int> endPair(searchable->getGoalState()->getStateRRepresentation().first,searchable->getGoalState()->getStateRRepresentation().second);
    			endNode = new State<pair<int,int>>(endPair);
    			startNode->setH(h(startNode,endNode));
    			startNode->setF(startNode->getH());
    			startNode->setG(0);
    			startNode->setCost(searchable->getStructure()[startNode->getStateRRepresentation().first][startNode->getStateRRepresentation().second]);
    			endNode->setCost(searchable->getStructure()[endNode->getStateRRepresentation().first][endNode->getStateRRepresentation().second]);
    			open.push_back(startNode);
    			while (!open.empty())
    			{
    				State<pair<int,int>>* currentNode = this->getMinNode();
    				if(this->isGoal(currentNode)){
    					string s =  backTrace(currentNode);
    					mtx.unlock();
    					return s;
    				}
    				this->DeleteNodeFromOpen(currentNode);
    				evaluatedNodes++;
    				closed.push_back(currentNode);
    				vector<State<pair<int,int>>*> neighbors = this->getAllSideNodes(currentNode);
    				for(State<pair<int,int>>* neighbor : neighbors) {
    					int tentative_gScore = currentNode->getG() + neighbor->getCost();
    					if(tentative_gScore <= neighbor->getG())
    					{
    						neighbor->setCameFrom(currentNode);
    						neighbor->setG(tentative_gScore);
    						neighbor->setF(neighbor->getG() + h(neighbor,endNode));
    						if(!isNodeinOpen(neighbor)&&(!isNodeinClose(neighbor)))
    						{
    							open.push_back(neighbor);
    						}
    					}
    				}
    			}
                string minus1 = "no path to goal";
                mtx.unlock();
                return minus1;
    }
	string backTrace(State<pair<int,int>>*st){
		vector<State<pair<int,int>>*> states;
		string s = "";
		while(!st->Equals(searchable1->getInitialState()))
		{
			states.push_back(st);
			st = st->getCameFrom();
		}
		states.push_back(searchable1->getInitialState());
		std::reverse(states.begin(),states.end());
		int sum = searchable1->getStructure()[searchable1->getInitialState()->getStateRRepresentation().first][searchable1->getInitialState()->getStateRRepresentation().second];
		for(int i = 0;i<states.size();i++)
		{
			if(i+1<states.size())
			{
				pair<int,int> p0 = states[i]->getStateRRepresentation();
				pair<int,int> p1 = states[i+1]->getStateRRepresentation();
				if(p1.first>p0.first){
					s+="Down ";
				}
				if(p1.first<p0.first){
					s+="Up ";
				}
				if(p1.second>p0.second){
					s+="Right ";
				}
				if(p1.second<p0.second){
					s+="Left ";
				}
				sum += searchable1->getStructure()[states[i+1]->getStateRRepresentation().first][states[i+1]->getStateRRepresentation().second];
				s+= "(" + std::to_string(sum)  + ")";
				if(i!=states.size()-2){s+=",";}
			}
		}
		return s;
	}
	double sumOfShortestPath(State<pair<int,int>>*st,Searchable<pair<int,int>>* searchable) {
		double sum = 0;
		while(!st->Equals(searchable->getInitialState()))
		{
			sum += searchable->getStructure()[st->getStateRRepresentation().first][st->getStateRRepresentation().second];
			st = st->getCameFrom();
		}
		sum+=searchable->getStructure()[searchable->getInitialState()->getStateRRepresentation().first][searchable->getInitialState()->getStateRRepresentation().second];
		return sum;
	}
    int getNumberOfNodesEvaluate() {
    	return this->evaluatedNodes;
    }
    int h (State<pair<int,int>>* begin ,State<pair<int,int>>* end ){
    	return abs(end->getStateRRepresentation().first-begin->getStateRRepresentation().first)
    	+ abs(end->getStateRRepresentation().second-begin->getStateRRepresentation().second);
    }
    void SetAstarCost(int distance,int cost, int upperDistance,State<pair<int,int>> *stateIt){
        stateIt->setCost(distance + cost - upperDistance);
    }
    State<pair<int,int>>* getMinNode() {
    	State<pair<int,int>>* min = new State<pair<int,int>>();
    	min->setF(100000);
		for(int i=0;i<open.size();i++)
		{
			if(open[i]->getF()<min->getF())
			{
				min = open[i];
			}
		}
		return min;
    }
    bool isGoal(State<pair<int,int>>*node){
    	return ((node->getStateRRepresentation().first==endNode->getStateRRepresentation().first)&&(node->getStateRRepresentation().second==endNode->getStateRRepresentation().second));
    }
    vector<State<pair<int,int>>*> getAllSideNodes(State<pair<int,int>>* current) {
    	int size = this->searchable1->getStructure().size();
		vector<State<pair<int,int>>*> AllPossibleStates;
		int r = current->getStateRRepresentation().first;
		int c = current->getStateRRepresentation().second;
		int dr[] = {-1,1,0,0};
		int dc[] = {0,0,1,-1};
		int rr;
		int cc;
		for(int i = 0; i < 4; i++)
		{
			rr = r + dr[i];
			cc = c + dc[i];
			if ((rr<0) || (cc<0)) {continue;}
			if ((rr>=size) || (cc>=size)) {continue;}
			if (this->searchable1->getStructure()[rr][cc] == -1) {continue;}
			pair<int,int> p(rr,cc);
			State<pair<int,int>>*n = new State<pair<int,int>>(p);
			n->setCameFrom(current);
			n->setG(current->getG()+this->searchable1->getStructure()[rr][cc]);
			n->setH(h(n,endNode));
			n->setF(n->getG()+n->getH());
			n->setCost(this->searchable1->getStructure()[rr][cc]);
			AllPossibleStates.push_back(n);
		}
		return AllPossibleStates;
	}
    void DeleteNodeFromOpen(State<pair<int,int>>*node) {
    	for (std::vector<State<pair<int,int>>*>::iterator it = open.begin() ; it != open.end(); ++it)
		{
			if((node->getStateRRepresentation().first==(*it)->getStateRRepresentation().first)&&(node->getStateRRepresentation().second==(*it)->getStateRRepresentation().second))
			{
				open.erase(it);
				break;
			}
		}
    }
    bool isNodeinOpen(State<pair<int,int>>*node) {
    	for (std::vector<State<pair<int,int>>*>::iterator it = open.begin() ; it != open.end(); ++it)
		{
			if((node->getStateRRepresentation().first==(*it)->getStateRRepresentation().first)&&(node->getStateRRepresentation().second==(*it)->getStateRRepresentation().second))
			{
				return true;
			}
		}
    	return false;
    }
    bool isNodeinClose(State<pair<int,int>>*node){
    	for (std::vector<State<pair<int,int>>*>::iterator it = closed.begin() ; it != closed.end(); ++it)
		{
			if((node->getStateRRepresentation().first==(*it)->getStateRRepresentation().first)&&(node->getStateRRepresentation().second==(*it)->getStateRRepresentation().second))
			{
				return true;
			}
		}
    	return false;
    }
};

#endif /* ASTAR2_H_ */
