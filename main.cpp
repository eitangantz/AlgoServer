

#include "MySerialServer.h"
#include "FileCacheManager.h"
#include "StringReverser.h"
#include "MyTestClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include "ClientHandler.h"
#include "Matrix.h"
#include "State.h"
#include "BFS.h"
#include "Searchable.h"
#include "DFS.h"
#include "Matrix.h"
#include "MatrixClientHandler.h"
#include "Adaptor.h"
#include "Isearcher.h"
#include "Astar2.h"
#include "BestFS2.h"
#include "MyParallelServer.h"
using namespace std;
int main(int argc, char *argv[]) {
	int port = stoi(argv[1]);
	MyParallelServer parallel;
	CacheManager<string,string>* cache = new FileCacheManager(5);
	Isearcher<string,pair<int,int>>* astar = new Astar2();
	Solver<Searchable<pair<int,int>>*,string>* solver = new Adaptor<Searchable<pair<int,int>>*,string,pair<int,int>>(astar);
	ClientHandler* clientHandler = new MatrixClientHandler(solver,cache);
	parallel.open(port, clientHandler);
	return 0;
}
