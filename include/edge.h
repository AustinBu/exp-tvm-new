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

    void setStart(Node* start);
    
    Node* getEnd() const;

    void setEnd(Node* end);

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

    void set_start(Edge* edge, Node* start);

    void set_end(Edge* edge, Node* end);
}

#endif // EDGE_H