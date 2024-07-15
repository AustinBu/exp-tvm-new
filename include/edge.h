#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include "node.h"

class Edge {
public:
    Edge();

    Edge(Node* start, Node* end);
    
    Node* getStart() const;
    
    Node* getEnd() const;

private:
    Node* start;
    Node* end;
};

#endif // EDGE_H