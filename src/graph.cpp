#include <iostream>
#include "../include/graph.h"
#include "../include/edge.h"
#include "../include/pattern_finder.h"

#include <cassert>


Graph::Graph() {}

Graph::Graph(List* e) {
    this->edgeList = e;
}

Graph::~Graph() {}

Graph* new_graph(List* e) { return new Graph(e); }

List* Graph::getEdgeList() {
    return edgeList;
}

List* pattern_find(Graph* g, int* pattern, int patternsize) {
    std::vector<int> returnEdges;
    Edge* edges = g->getEdgeList()->getEdge();

    for (int i = 0; i < g->getEdgeList()->getSize(); i++) {
        if (edges[i].getStart()->getOpcode() == pattern[0]) {
            if (edges[i].getEnd()->getOpcode() == pattern[1]) {
                returnEdges.push_back(edges[i].getId());
            }
        }
    }

    int* arr = new int(returnEdges.size());
    std::memcpy(arr, returnEdges.data(), returnEdges.size() * sizeof(int));
    void* void_ptr = static_cast<void*>(arr);

    return new List(void_ptr, returnEdges.size(), INT);
}

void del_graph(bool debug, Graph* graph) {
    if (debug) { std::cout << "Deleting graph: " << graph << std::endl; }
    delete graph;
}
