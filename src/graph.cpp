#include "../include/graph.h"
#include "../include/edge.h"

Graph::Graph() {}

void Graph::addEdge(Edge* e) {
    std::cout << (*e->getStart()).getOpcode() << std::endl;
    adjList[*e->getStart()].push_back(*e->getEnd());
    std::cout << adjList[*e->getStart()][0].getOpcode() << std::endl;
}

std::unordered_map<Node, std::vector<Node> >& Graph::getAdjList() {
    return adjList;
}

void Graph::printGraph() const {
    for (const auto& pair : adjList) {
        std::cout << "Node " << pair.first.getId() << " (opcode " << pair.first.getOpcode() << "): ";
        for (const Node& node : pair.second) {
            std::cout << node.getId() << " ";
        }
        std::cout << std::endl;
    }
}

extern "C" {
    Graph* new_graph() { return new Graph(); }

    void add_edge(Graph* g, Edge* e) {
        g->addEdge(e);
    }

    void print_graph(Graph* g) {
        g->printGraph();
    }
}