#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include "node.h"

class Node;

class Edge {
public:
    Edge();

    Edge(Node* start, Node* end);

    ~Edge();
    
    Node* getStart() const;
    
    Node* getEnd() const;

    int getId() const;

private:
    Node* start;
    Node* end;
    int id;
    static int nextId;
};

extern "C" {
    Edge* new_edge(Node* start, Node* end);

    void del_edge(bool debug, Edge* edge);

    int edge_get_id(Edge* edge); 
}

#endif // EDGE_H