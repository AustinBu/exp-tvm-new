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

    std::unordered_map<Node, std::vector<Node>>& getAdjList();

    void toNativeGraph(std::vector<int>& nodeIds, std::vector<int>& nodeOps,
                       std::vector<size_t>& edgeStartIdx, std::vector<size_t>& edgeEndIdx);

    void printGraph() const;

private:
    std::unordered_map<Node, std::vector<Node>> adjList;
};

#endif // GRAPH_H