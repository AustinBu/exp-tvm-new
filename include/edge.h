#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include "node.h"

class Edge {
public:
    Edge();

    Edge(Node* start, Node* end);

private:
    Node* start;
    Node* end;
};

#endif // EDGE_H