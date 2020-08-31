/*
 * MatrixClientHandler.h
 *
 *  Created on: 18 Jan 2020
 *      Author: eitan
 */

#ifndef MATRIXCLIENTHANDLER_H_
#define MATRIXCLIENTHANDLER_H_
#include "Solver.h"
#include "CacheManager.h"
#include "ClientHandler.h"
#include "Matrix.h"
#include <string>
#include <list>
#include <vector>
using namespace std;
#include <string>
#include <fstream>
#include <list>
#include <iostream>
#include <unordered_map>
#include <iterator>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <typeinfo>
#include <bits/stdc++.h>
#include <unistd.h>
#include <strings.h>
class MatrixClientHandler : public ClientHandler{
private:
Solver<Searchable<pair<int,int>>*,string>* s;
CacheManager<string,string>* c;
public:
MatrixClientHandler(Solver<Searchable<pair<int,int>>*,string>* solver,CacheManager<string,string>* cache){
		s = solver;
		c = cache;
}
virtual ~MatrixClientHandler(){}
void handleClient(int clientsocket) {
		vector<string>input;
    	char buffer[4096];
        string buf;
		while(buf.find("end\n") == string::npos) {
	    memset(buffer, 0, 4096);
        // Wait for client to send data
        int bytesReceived = read(clientsocket, buffer, 4096);
        if (bytesReceived == -1)
        {
            cerr << "Error in recv(). Quitting" << endl;
            close(clientsocket);
            return;
        }

        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            return;
        }
                buf = string(buffer);
                input.push_back(buf);
		}
		Searchable<pair<int,int>>* m = this->convertInputToMatrix(input);
        string problem(m->to_Hash_string());
        string sulotion;
        if((!(c->isSinTheCache(problem)))&&(!(c->isFileExist(problem)))) {
        	sulotion = s->slove(m);
        	c->insertSulotion(problem, sulotion);
        } else {
        	sulotion = c->getSoultion(problem);
        }
        send(clientsocket , sulotion.c_str() , strlen(sulotion.c_str()) , 0 );
	}
void stop() {

}
Searchable<pair<int,int>>* convertInputToMatrix(vector<string>input) {
    vector<vector<int>> matrix;
    vector<pair<int,int>> pairs;
    vector<string> lines;
    string mat = "";
    for (string str : input){
    	mat += str;
    }
	   stringstream s_stream(mat); //create string stream from the string
	   while(s_stream.good()) {
	      string substr;
	      getline(s_stream, substr, '\n'); //get first string delimited by comma
	      lines.push_back(substr);
	   }
	   lines.pop_back();
	   lines.pop_back();
    for (string line : lines) {
    		vector<int> l;
    	   stringstream s_stream(line); //create string stream from the string
    	   while(s_stream.good()) {
    	      string substr;
    	      getline(s_stream, substr, ','); //get first string delimited by comma
    	      l.push_back(stoi(substr));
    	   }
    	   if(l.size()!=2) {
    	   matrix.push_back(l);
    	   } else {
    		   pair<int,int> p(l.front(),l.back());
    		   pairs.push_back(p);
    	   }
    }
    int sizeofthematrix = matrix.front().size();
    State<pair<int,int>>* initialState = new State<pair<int,int>>(pairs[0]);
    State<pair<int,int>>* goalState = new State<pair<int,int>>(pairs[1]);
    Searchable<pair<int,int>>* m = new Matrix(matrix,initialState,goalState,sizeofthematrix);
    return m;
}
};
#endif /* MATRIXCLIENTHANDLER_H_ */
