#include "../include/node.h"
#include "../include/edge.h"

Edge::Edge() {}

Edge::Edge(Node* start, Node* end)
    : start(start), end(end) {}

Edge::~Edge() {}


Node* Edge::getStart() const {
    return start;
}

Node* Edge::getEnd() const {
    return end;
}

Edge* new_edge(Node* start, Node* end) { return new Edge(start, end); }

void del_edge(bool debug, Edge* edge) {
    if (debug) { std::cout << "Deleting edge: " << edge << std::endl; }
    delete edge;
}
