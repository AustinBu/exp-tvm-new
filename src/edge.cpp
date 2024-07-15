#include "../include/node.h"
#include "../include/edge.h"

Edge::Edge() {}

Edge::Edge(Node* start, Node* end)
    : start(start), end(end) {}

Node* Edge::getStart() const {
    return start;
}

Node* Edge::getEnd() const {
    return end;
}

extern "C" {
    Edge* new_edge(Node* start, Node* end) { return new Edge(start, end); }
}