#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include "node.h"

class Edge {
public:
    Edge();

    Edge(Node* start, Node* end);

    ~Edge();
    
    Node* getStart() const;
    
    Node* getEnd() const;

private:
    Node* start;
    Node* end;
};

extern "C" {
    Edge* new_edge(Node* start, Node* end);

    void del_edge(Edge* edge);
}

#endif // EDGE_H