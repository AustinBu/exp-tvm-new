#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include "node.h"
#include "edge.h"

class Graph {
public:
    Graph();

    Graph(List* e);

    ~Graph();

    List* getEdgeList();

private:
    List* edgeList;
};

extern "C" {
    Graph* new_graph(List* e);

    List* pattern_find(Graph* g, int* pattern, int patternsize);

    void del_graph(bool debug, Graph* graph);
}
#endif // GRAPH_H