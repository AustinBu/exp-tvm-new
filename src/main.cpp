#include <iostream>
#include "../include/graph.h"
#include "../include/edge.h"
#include "../include/node.h"

int main() {
    // Create nodes
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);

    // Create edges
    Edge* edge1 = new Edge(node1, node2);
    Edge* edge2 = new Edge(node2, node3);
    Edge* edge3 = new Edge(node3, node4);

    // Create a new graph
    Graph* graph = new Graph();

    // Add edges to the graph
    graph->addEdge(edge1);
    graph->addEdge(edge2);
    graph->addEdge(edge3);

    // Verify the adjacency list
    const std::unordered_map<Node, std::vector<Node> >& adjList = graph->getAdjList();

    for (const auto& pair : adjList) {
        std::cout << "Node " << pair.first.getId() << ": ";
        for (Node n : pair.second) {
            std::cout << n.getId() << " ";
        }
        std::cout << std::endl;
    }

    // Clean up
    delete edge1;
    delete edge2;
    delete edge3;
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete graph;

    return 0;
}
