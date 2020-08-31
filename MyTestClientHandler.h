/*
 * MyTestClientHandler.h
 *
 *  Created on: 13 Jan 2020
 *      Author: eitan
 */

#ifndef MYTESTCLIENTHANDLER_H_
#define MYTESTCLIENTHANDLER_H_
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

class MyTestClientHandler :public ClientHandler {
private:
bool shouldStop;
Solver<string,string>* s;
CacheManager<string,string>* c;

public:
	MyTestClientHandler(Solver<string,string>* solver,CacheManager<string,string>* cache);
	virtual ~MyTestClientHandler();
	void handleClient(int clientsocket);
	void stop();
};

#endif /* MYTESTCLIENTHANDLER_H_ */
