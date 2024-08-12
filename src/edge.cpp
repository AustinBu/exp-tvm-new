#include "../include/node.h"
#include "../include/edge.h"

int Edge::nextId = 1;

Edge::Edge() : id(nextId++) {}

Edge::Edge(Node* start, Node* end)
    : start(start), end(end), id(nextId++) {}

Edge::~Edge() {}


Node* Edge::getStart() const {
    return start;
}

void Edge::setStart(Node* start) {
    this->start = start;
}

Node* Edge::getEnd() const {
    return end;
}

void Edge::setEnd(Node* end) {
    this->end = end;
}

int Edge::getId() const {
    return id;
}

Edge* new_edge(Node* start, Node* end) { return new Edge(start, end); }

void del_edge(bool debug, Edge* edge) {
    if (debug) { std::cout << "Deleting edge: " << edge << std::endl; }
    delete edge;
}

int edge_get_id(Edge* edge) { return edge->getId(); }

void set_start(Edge* edge, Node* start) {
    edge->setStart(start);
}

void set_end(Edge* edge, Node* end) {
    edge->setEnd(end);
}