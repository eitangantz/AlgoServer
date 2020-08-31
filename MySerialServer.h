/*
 * MySerialServer.h
 *
 *  Created on: 13 Jan 2020
 *      Author: eitan
 */

#ifndef MYSERIALSERVER_H_
#define MYSERIALSERVER_H_
#include "Server.h"
class MySerialServer : public server_side::Server {
private:
bool shouldStop;
public:
	MySerialServer();
	virtual ~MySerialServer();
	void open(int port,ClientHandler* c);
	void stop();
};

#endif /* MYSERIALSERVER_H_ */
