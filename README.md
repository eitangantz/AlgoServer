# AlgoServer

Our goal is to host a client at our server and find the "quickest path" for the matrix that the client will input to the program.

our program is a specific implementation of our Server and Client Handler interfaces

The Server handling various clients at any given moment.

The requests given to the Server are pathfinding in a graph (more precisley a matrix Graph when you give the start and goal matrix with costs to "step" into defined by the data you are sending to the server at the specific index), which is sent line by line (creating the matrix of costs) by the client.

The algorithm we chose to use is A*, but implementations for BEST FIRST SEARCH (in the Dijkstra context of shortest path...) and classic DFS and BFS are also implemented.
