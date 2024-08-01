#include <iostream>
#include "../include/graph.h"
#include "../include/edge.h"
#include "../include/pattern_finder.h"

#include <cassert>


Graph::Graph() {}

Graph::Graph(List* e) {
    this->edgeList = e;
    std::cout << this->edgeList->getEdge()->getId() << std::endl;
    std::cout << this->edgeList->getEdge()->getStart()->getOpcode() << std::endl;

}

Graph::~Graph() {}

Graph* new_graph(List* e) { return new Graph(e); }

List* Graph::getEdgeList() {
    return edgeList;
}

int* pattern_find(Graph* g, int* pattern, int patternsize) {
    std::vector<int> returnEdges;
    Edge* edges = g->getEdgeList()->getEdge();

    for (int i = 0; i < g->getEdgeList()->getSize(); i++) {
        if (edges[i].getStart()->getOpcode() == pattern[0]) {
            if (edges[i].getEnd()->getOpcode() == pattern[1]) {
                returnEdges.push_back(edges[i].getId());
            }
        }
    }

    int* arr = returnEdges.data();

    for (size_t i = 0; i < returnEdges.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return returnEdges.data();
}

void del_graph(bool debug, Graph* graph) {
    if (debug) { std::cout << "Deleting graph: " << graph << std::endl; }
    delete graph;
}
