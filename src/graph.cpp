#include "../include/graph.h"
#include "../include/edge.h"

Graph::Graph() {}

void Graph::addEdge(Edge* e) {
    adjList[*e->getStart()].push_back(*e->getEnd());
}

std::unordered_map<Node, std::vector<Node> >& Graph::getAdjList() {
    return adjList;
}

extern "C" {
    Graph* new_graph() { return new Graph(); }

    void add_edge(Graph* g, Edge* e) {
        g->addEdge(e);
    }
}