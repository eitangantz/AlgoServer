/*
 * BFS.h
 *
 *  Created on: 17 Jan 2020
 *      Author: eitan
 */

#ifndef BFS_H_
#define BFS_H_
#include <string>
#include "Isearcher.h"
#include "Searchable.h"
#include <queue>
#include <algorithm>
class BFS : public Isearcher<string,pair<int,int>>{
private:
int evaluatedNodes = 0;
public:
	BFS(){}
	virtual ~BFS(){}

    int getNumberOfNodesEvaluate() {
    	return this->evaluatedNodes;
    }
    string search(Searchable<pair<int,int>>* searchable) {

    			int flag = 0;
    			vector<State<pair<int,int>>*> visitedNodes;
                queue<State<pair<int,int>>*> q;
                searchable->getInitialState()->setVisited();
                visitedNodes.push_back(searchable->getInitialState());
                q.push(searchable->getInitialState());
                searchable->getInitialState()->setDistance(0);

                while (!q.empty()) {

                	State<pair<int,int>>* p = q.front();
                    q.pop();
                    evaluatedNodes++;
                    vector<State<pair<int,int>>*> allpossiblestates = searchable->getAllPossibleStates(p);
                    for(int i = 0;i<allpossiblestates.size();i++)  {
                    	if(allpossiblestates[i]->getStateRRepresentation()==searchable->getGoalState()->getStateRRepresentation()) {
                    		searchable->setGoalState(allpossiblestates[i]);
                    		return this->backTrace(allpossiblestates[i], searchable);
                    	}
                    	for(int j = 0;j<visitedNodes.size() ;j++)
                    	{
                    		if(allpossiblestates[i]->getStateRRepresentation()==visitedNodes[j]->getStateRRepresentation())
                    		{
                    			flag = 1;
                    		}
                    	}
                    	if(flag == 1){
                    		flag = 0;
                    		continue;
                    	}
                    	q.push(allpossiblestates[i]);
                    	allpossiblestates[i]->setVisited();
                    	visitedNodes.push_back(allpossiblestates[i]);
                    }
                }
                string minus1 = "no path";
                return minus1;
    }
	string backTrace(State<pair<int,int>>*st,Searchable<pair<int,int>>* searchable){
		vector<State<pair<int,int>>*> states;
		string s = "";
		while(!st->Equals(searchable->getInitialState()))
		{
			states.push_back(st);
			st = st->getCameFrom();
		}
		states.push_back(searchable->getInitialState());
		std::reverse(states.begin(),states.end());
		int sum = searchable->getStructure()[searchable->getInitialState()->getStateRRepresentation().first][searchable->getInitialState()->getStateRRepresentation().second];
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
				sum += searchable->getStructure()[states[i+1]->getStateRRepresentation().first][states[i+1]->getStateRRepresentation().second];
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
			sum += st->getCost();
			st = st->getCameFrom();
		}
		sum+=searchable->getInitialState()->getCost();
		return sum;
	}
};

#endif /* BFS_H_ */
