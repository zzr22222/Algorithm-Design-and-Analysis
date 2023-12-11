**Project Name:** Finding All Bridges in an Undirected Graph

**Project Goal:** 

1. **Definition of a Bridge**

   In graph theory, an edge is called a "bridge" if its removal increases the number of connected components in the graph. Equivalently, an edge is a bridge if and only if it does not lie on any cycle. A graph can have zero or multiple bridges.

2. **Algorithm**

   (1) **Baseline Algorithm**

   For every edge (u, v), do the following:

   a) Remove (u, v) from the graph.

   b) Check if the graph remains connected (This can be done using either BFS or DFS).

   c) Add (u, v) back to the graph.

   (2) **Design a more efficient algorithm using Disjoint Set Union (DSU)**. Do not use the Tarjan algorithm. If the Tarjan algorithm is used, you still need to design a more efficient algorithm than the baseline algorithm using Disjoint Set Union.