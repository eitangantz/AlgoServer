/*
 * Server.h
 *
 *  Created on: 13 Jan 2020
 *      Author: eitan
 */

#ifndef SERVER_H_
#define SERVER_H_
#include "ClientHandler.h"
namespace server_side {

class Server {
public:
	Server(){}
	virtual ~Server(){}
	virtual void open(int port,ClientHandler* c) = 0;
	virtual void stop() = 0;
};

} /* namespace server_side */

#endif /* SERVER_H_ */
