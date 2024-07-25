#include "../include/graph.h"
#include "../include/edge.h"

#include <cassert>


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

void Graph::toNativeGraph(std::vector<int>& nodeIds, std::vector<int>& nodeOps,
                          std::vector<size_t>& edgeStartIdx, std::vector<size_t>& edgeEndIdx) {

    // mapping from nodeId to nodeIdx
    std::unordered_map<int, size_t> nodeIndices;

    for (const auto& pair : adjList) {
        if (!nodeIndices.count(pair.first.getId())) {
            nodeIndices[pair.first.getId()] = nodeIds.size();
            nodeIds.push_back(pair.first.getId());
            nodeOps.push_back(pair.first.getOpcode());
        }

        for (const auto& endPoint : pair.second) {
            if (!nodeIndices.count(endPoint.getId())) {
                nodeIndices[endPoint.getId()] = nodeIds.size();
                nodeIds.push_back(endPoint.getId());
                nodeOps.push_back(endPoint.getOpcode());
            }
        }
    }

    for (const auto& pair : adjList) {
        for (const auto& endPoint : pair.second) {
            assert(nodeIds[nodeIndices[endPoint.getId()]] == endPoint.getId());

            edgeStartIdx.push_back(nodeIndices[pair.first.getId()]);
            edgeEndIdx.push_back(nodeIndices[endPoint.getId()]);
        }
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
