/*
 * MySerialServer.cpp
 *
 *  Created on: 13 Jan 2020
 *      Author: eitan
 */

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
#include <unistd.h>
MySerialServer::MySerialServer() {
shouldStop = false;
}

MySerialServer::~MySerialServer() {
	// TODO Auto-generated destructor stub
}
void MySerialServer::open(int port, ClientHandler* c) {
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

    // Tell Winsock the socket is for listening
    if( listen(listening, SOMAXCONN)<0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    timeval timeout;
    timeout.tv_sec = 20;
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
            close(listening);
            exit(2);
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
    c->handleClient(clientSocket);
    cout<<"after handle"<<endl;
    }
}
void MySerialServer::stop() {
	shouldStop = true;
}
