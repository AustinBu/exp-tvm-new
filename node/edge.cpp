#include "../include/node.h"
#include "../include/edge.h"

Edge::Edge() {}

Edge::Edge(Node* start, Node* end)
    : start(start), end(end) {}

extern "C" {
    Edge* new_edge(Node* start, Node* end) { return new Edge(start, end); }
}