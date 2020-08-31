# AlgoServer

The server goal is to host a client and find the "quickest path" for the matrix that the client will input to the program.

The Server handling various clients at any given moment.

The requests given to the Server are pathfinding in a graph (more precisley a matrix Graph when you give the start and goal matrix with costs to "step" into defined by the data you are sending to the server at the specific index), which is sent line by line (creating the matrix of costs) by the client.

from an experiment i made on over 100 matrix the A* algorithm showed the best results(as you can see in the Diagram file) so i picked it , but implementations for BEST FIRST SEARCH (in the Dijkstra context of shortest path...) and classic DFS and BFS are also implemented.
