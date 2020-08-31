/*
 * MyTestClientHandler.cpp
 *
 *  Created on: 13 Jan 2020
 *      Author: eitan
 */

#include "MyTestClientHandler.h"
#include "MySerialServer.h"
#include <string>
#include <list>
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
#include <bits/stdc++.h>
MyTestClientHandler::MyTestClientHandler(Solver<string,string>* solver,CacheManager<string,string>* cache) {
	s = solver;
	c = cache;
	shouldStop = false;
}

MyTestClientHandler::~MyTestClientHandler() {
	// TODO Auto-generated destructor stub
}
void MyTestClientHandler::handleClient(int clientSocket) {
		shouldStop = false;
		while(!shouldStop) {
    	char buf[4096];
        memset(buf, 0, 4096);
        // Wait for client to send data
        cout<<"IN HANDLE"<<endl;
        int bytesReceived = read(clientSocket, buf, 4096);
        if (bytesReceived == -1)
        {
            cerr << "Error in recv(). Quitting" << endl;
            this->stop();
            break;
        }

        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            this->stop();
            break;
        }
        cout<<"byte: ";
        cout<<(bytesReceived)<<endl;
        string problem = "";
        int x = 0;
        while (buf[x] != '\n') {
        	if(buf[x]!='\r') {
        	problem +=buf[x];
        	}
        	x++;
        }
        cout<<"size of problem: ";
        cout<<strlen(problem.c_str())<<endl;
        if(problem != "end") {
        string sulotion;
        if((!(c->isSinTheCache(problem)))&&(!(c->isFileExist(problem)))) {

        	sulotion = s->slove(problem);
        	c->insertSulotion(problem, sulotion);
        } else {
        	cout<<"im just before getSoulution"<<endl;
        	sulotion = c->getSoultion(problem);
        }
        cout<<sulotion.c_str()<<endl;
        cout<<strlen(sulotion.c_str())<<endl;
        send(clientSocket , sulotion.c_str() , strlen(sulotion.c_str()) , 0 );
        } else {
        	cout<<"exit handleclient becasue of end pressed"<<endl;
        	this->stop();
        }
	}
}
void MyTestClientHandler::stop() {
	shouldStop = true;
}
