/*
 * HandleParallel.h
 *
 *  Created on: 22 Jan 2020
 *      Author: eitan
 */

#ifndef HANDLEPARALLEL_H_
#define HANDLEPARALLEL_H_
#include <thread>
#include "ClientHandler.h"
class HandleParallel {
public:
	HandleParallel(){}
	virtual ~HandleParallel(){}
	void ThreadClientHandle(int clientSocket1, ClientHandler*cl) {
		cl->handleClient(clientSocket1);
		pthread_exit(nullptr);
	}
};

#endif /* HANDLEPARALLEL_H_ */
