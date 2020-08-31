/*
 * ClientHandler.h
 *
 *  Created on: 13 Jan 2020
 *      Author: eitan
 */

#ifndef CLIENTHANDLER_H_
#define CLIENTHANDLER_H_
#include <iostream>
using namespace std;
class ClientHandler {
public:
	ClientHandler(){}
	virtual ~ClientHandler(){}
	virtual void handleClient(int clientsocket) = 0;
};

#endif /* CLIENTHANDLER_H_ */
