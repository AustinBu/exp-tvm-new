#include <iostream>
#include "../include/graph.h"
#include "../include/edge.h"
#include "../include/node.h"
#include "../include/pattern_finder.h"

int main() {
    // Create nodes
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    Node* node5 = new Node(5);
    Node* node6 = new Node(3);
    Node* node7 = new Node(2);

    std::cout << node1->getOpcode() << std::endl;

    // Create edges
    Edge edge1(node1, node2);
    Edge edge2(node2, node3);
    Edge edge3(node3, node4);
    Edge edge4(node5, node2);
    Edge edge5(node6, node3);
    Edge edge6(node7, node3);

    // Create a new graph
    Graph graph;

    // Add edges to the graph
    graph.addEdge(&edge1);
    graph.addEdge(&edge2);
    graph.addEdge(&edge3);
    graph.addEdge(&edge4);
    graph.addEdge(&edge5);
    graph.addEdge(&edge6);

    // Verify the adjacency list
    // const std::unordered_map<Node, std::vector<Node> >& adjList = graph->getAdjList();

    // for (const auto& pair : adjList) {
    //     std::cout << "Node " << pair.first.getId() << ": ";
    //     for (Node n : pair.second) {
    //         std::cout << n.getId() << " ";
    //     }
    //     std::cout << std::endl;
    // }

    graph.printGraph();

    expedera::PatternGraph* patterns = expedera::PatternGraph::newGraph();

    size_t idx4 = patterns->addParent(4);
    patterns->setChildIdx(idx4);
    size_t idx3 = patterns->addParent(3);
    patterns->setChildIdx(idx3);
    patterns->addParent(3);
    patterns->addParent(2);

    // converting the graph representation to index representation
    std::vector<int> nodeIds;
    std::vector<int> nodeOps;
    std::vector<size_t> edgeStartIdx;
    std::vector<size_t> edgeEndIdx;

    graph.toNativeGraph(nodeIds, nodeOps, edgeStartIdx, edgeEndIdx);

    std::vector<std::vector<int>> matchedIndicesVec;

    expedera::findPatterns(nodeIds, nodeOps, edgeStartIdx, edgeEndIdx, *patterns, matchedIndicesVec);

    std::printf("------------------------\n");

    for (const auto& matchedIndices: matchedIndicesVec) {
        for (const int& matchedId: matchedIndices) {
            std::printf("id: %d\n", matchedId);
        }
        std::printf("------------------------\n");
    }

    // Clean up
    expedera::PatternGraph::deleteGraph(patterns);

    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
    delete node6;
    delete node7;

    return 0;
}
