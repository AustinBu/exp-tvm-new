#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include "node.h"
#include "edge.h"

class Graph {
public:
    Graph();

    void addEdge(Edge* e);

    std::unordered_map<Node, std::vector<Node> >& getAdjList();

    void printGraph() const;

private:
    std::unordered_map<Node, std::vector<Node> > adjList;
};

#endif // GRAPH_H