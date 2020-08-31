/*
 * MyParallelServer.h
 *
 *  Created on: 22 Jan 2020
 *      Author: eitan
 */

#ifndef MYPARALLELSERVER_H_
#define MYPARALLELSERVER_H_
#include "Server.h"
#include <vector>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
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
#include <unistd.h>
#include "HandleParallel.h"
using namespace std;
class MyParallelServer : public server_side::Server{
private:
bool shouldStop;
vector<thread> threads;
public:
	MyParallelServer(){shouldStop  = false;}
	virtual ~MyParallelServer(){}
	void open(int port,ClientHandler* c) {
	    // Create a socketv
	    int listening = socket(AF_INET, SOCK_STREAM, 0);
	    if (listening == 0)
	    {
	        cerr << "Can't create a socket! Quitting" << endl;
	        //return -1;
	    }

	    int opt = 1;
	    if (setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
	        perror("setsockopt");
	        exit(EXIT_FAILURE);
	    }

	    // Bind the ip address and port to a socket
	    sockaddr_in hint;
	    hint.sin_family = AF_INET;
	    hint.sin_addr.s_addr = INADDR_ANY;
	    hint.sin_port = htons(port);
	    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

	    if(bind(listening, (sockaddr*)&hint, sizeof(hint))<0){
	        perror("bind failed");
	        exit(EXIT_FAILURE);
	    }
	    memset(hint.sin_zero, '\0', sizeof hint.sin_zero);

	    // Tell Winsock the socket is for listening
	    if( listen(listening, SOMAXCONN)<0) {
	        perror("listen");
	        exit(EXIT_FAILURE);
	    }
	    timeval timeout;
	    timeout.tv_sec = 10;
	    timeout.tv_usec = 0;

	    setsockopt(listening, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
	    // Wait for a connection


	    while (!shouldStop) {
	    sockaddr_in client;
	    socklen_t clientSize = sizeof(client);

	    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	   if (clientSocket < 0) {
	        if (errno == EWOULDBLOCK)	{
	            cout << "timeout!" << endl;
	            this->stop();
	    	    close(listening);
	    	    break;
	        }	else	{
	            perror("other error");
	            exit(3);
	        }
	    }

	    char host[NI_MAXHOST];      // Client's remote name
	    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
	    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	    memset(service, 0, NI_MAXSERV);
	    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	    {
	        cout << host << " connected on port " << service << endl;
	    }
	    else
	    {
	        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
	        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
	    }
	    HandleParallel *h = new HandleParallel();
	    std::thread thread1(&HandleParallel::ThreadClientHandle,h,clientSocket,c);
	    threads.push_back(std::move(thread1));
	    }
	}
	void stop() {
	    for (auto &tr: this->threads) {
	        if (tr.joinable()) {
	            tr.join();
	        }
	    }
		shouldStop = true;
	}
};

#endif /* MYPARALLELSERVER_H_ */
