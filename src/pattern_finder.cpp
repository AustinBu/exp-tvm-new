#include <algorithm>
#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <map>

#include "../include/pattern_finder.h"

namespace expedera {

struct NodeId {
    const int id;

    NodeId(int id): id(id) {}

    bool operator==(const NodeId& other) const {
        return (id == -1 || other.id == -1 || id == other.id);
    }
};

struct OpCode {
    const int op;

    OpCode(int op): op(op) {}

    bool operator==(const OpCode& other) const {
        return (op == -1 || other.op == -1 || op == other.op);
    }
};

struct Node {
    const NodeId id;
    const OpCode op;

    Node(int id, int op): id(id), op(op) {}
};

struct Range {
    // iterate from start to end - 1;
    // for (size_t idx = start; idx < end; idx++) { ... }

    size_t start;
    size_t end;

    Range(size_t start, size_t end):
          start(start),
          end(end) {}

    size_t size() const {
        return (end - start);
    }
};

struct Edge {
    const NodeId startId;
    const NodeId endId;

    // saved here for convenience
    // op codes of the edge nodes
    const OpCode startOp;
    const OpCode endOp;

    // indices of the start and end nodes in the node list
    const size_t startIdx;
    const size_t endIdx;

    // todo: index is constructed hackily
    // should fetch the actual index in the node list
    Edge(int startId, int endId,
         int startOp, int endOp):
         startId(startId),
         endId(endId),
         startOp(startOp),
         endOp(endOp),
         startIdx(startId - 1),
         endIdx(endId - 1) {}

    Edge(int startId, int endId,
         int startOp, int endOp,
         size_t startIdx, size_t endIdx):
         startId(startId),
         endId(endId),
         startOp(startOp),
         endOp(endOp),
         startIdx(startIdx),
         endIdx(endIdx) {}
};

struct PatternGraphImpl : public PatternGraph {
    std::vector<OpCode> codes;
    std::vector<Range> parentRange;

    private:
    ssize_t childIdx;

    public:
    PatternGraphImpl() {
        childIdx = -1;
    }

    // mark the OpCode in the idx as the child
    void setChildIdx(size_t idx) override {
        // cannot edit previously inserted child
        // can ONLY move forward in the graph
        assert(childIdx <= (ssize_t) idx);

        childIdx = idx;
        parentRange[childIdx].start = codes.size();
    }

    size_t addParent(const int& code) override {
        return addParent(OpCode(code));
    }

    size_t addParent(const OpCode& code) {
        codes.emplace_back(code.op);
        parentRange.emplace_back(0, 0);

        // update the child's parent index
        if (childIdx != -1) {
            parentRange[childIdx].end = codes.size();
        }

        // return the index of the inserted code
        return codes.size() - 1;
    }

    bool hasOp(OpCode& code) const {
        return codes.end() != std::find(codes.begin(), codes.end(), code);
    }

    size_t size() const override {
        assert(codes.size() == parentRange.size());
        return codes.size();
    }
};

template<typename T, bool comp(const T&, const T&)>
static int sort_comp(const void* a, const void* b) {
    return comp(*(const T*)(a), *(const T*)(b));
}

template<typename T, bool comp(const T&, const T&)>
static void sort(std::vector<T>& vec) {
    std::qsort(vec.data(), vec.size(), sizeof(T), sort_comp<T, comp>);
}

static void print_edges(const std::vector<Edge>& edges) {
    for (const Edge& e : edges) {
        std::printf("startId: %d, endId: %d, startOp: %d, endOp: %d\n", e.startId.id, e.endId.id, e.startOp.op, e.endOp.op);
    }
}

static inline Range getRangeEnd(const std::vector<Edge>& edges, const NodeId& endId) {
    // edges need to be sorted by endId

    size_t start = std::distance(edges.begin(), std::lower_bound(edges.begin(), edges.end(), endId, [](const Edge &e, const NodeId& id) { return e.endId.id < id.id; }));
    size_t end = std::distance(edges.begin(), std::upper_bound(edges.begin(), edges.end(), endId, [](const NodeId& id, const Edge &e) { return e.endId.id > id.id; }));

    return Range(start, end);
}

struct Index {
    size_t patternIdx;
    size_t nodeIdx;

    Index(size_t patternIdx, size_t nodeIdx):
          patternIdx(patternIdx),
          nodeIdx(nodeIdx) {}
};

struct Work {
    std::vector<size_t> matchedNodeIndices;
    std::deque<Index> workIndices;

    // actually, we can store macthedIndices as a shared pointer
    // which will reduce the memory foot print
    // at the expense of compute?
    Work(const std::vector<size_t>& matchedNodeIndices,
         const std::deque<Index>& workIndices):
         matchedNodeIndices(matchedNodeIndices),
         workIndices(workIndices) {}
};

template<typename A, typename B, typename C>
static void generateCombinations(std::vector<A>& a, std::vector<B>& b,
                                 std::vector<std::vector<C>>& combOut, std::vector<C>& runningComb,
                                 const size_t pairsLen) {

    const size_t aSize = a.size();
    const size_t bSize = b.size();

    if (aSize == 0 || bSize == 0) {
        if (runningComb.size() == pairsLen) {
            combOut.push_back(runningComb);
        }

        return;
    }

    A aV = a[0];
    a.erase(a.begin());

    // all combinations a can be paired
    for (size_t bIdx = 0; bIdx < bSize; bIdx++) {
        B bV = b[bIdx];

        runningComb.emplace_back(aV, bV);

        b.erase(b.begin() + bIdx);

        generateCombinations(a, b, combOut, runningComb, pairsLen);

        b.insert(b.begin() + bIdx, bV);
        runningComb.pop_back();
    }

    // don't select any of b (skip a)
    generateCombinations(a, b, combOut, runningComb, pairsLen);

    a.insert(a.begin(), aV);
}

template<typename A, typename B, typename C>
static void generateCombinations(std::vector<A>& a, std::vector<B>& b, std::vector<std::vector<C>>& combOut) {
    std::vector<C> runningComb;
    generateCombinations(a, b, combOut, runningComb, std::min(a.size(), b.size()));
}

bool comp_edges(const Edge& a, const Edge& b) {
    if (a.startId.id > b.startId.id) {
        return true;
    } else if (a.startId.id < b.startId.id) {
        return false;
    } else {
        return a.endId.id > b.endId.id;
    }
}

bool comp_edges_end(const Edge& a, const Edge& b) {
    if (a.endId.id > b.endId.id) {
        return true;
    } else if (a.endId.id < b.endId.id) {
        return false;
    } else {
        return a.startId.id > b.startId.id;
    }
}

void findPatterns(const std::vector<Node>& nodes, const std::vector<size_t>& possibleEndPoints,
                  const std::vector<Edge>& edges, const PatternGraphImpl& patterns,
                  std::vector<std::vector<NodeId>>& matchedNodesIds,
                  const bool strict = false) {

    // std::printf("Starting\n");

    // used to index into the nodes and corresponding patterns
    // each combination can lead to creating multiple paths which
    // need to be explored. That's why a list of list.
    std::deque<Work> workingIndices;

    for (size_t idx = 0; idx < possibleEndPoints.size(); idx++) {
        // all possible end points
        // which start at the child most pattern

        // nothing matched yet
        std::vector<size_t> currentMatchedNodeIndices;
        std::deque<Index> currentWorkingIndices;

        currentWorkingIndices.emplace_back(0, possibleEndPoints[idx]);

        workingIndices.emplace_back(currentMatchedNodeIndices, currentWorkingIndices);
    }

    while (!workingIndices.empty()) {
        Work work = workingIndices.back();
        workingIndices.pop_back();

        std::vector<size_t>& matchedNodeIndices = work.matchedNodeIndices;
        std::deque<Index>& indices = work.workIndices;
        bool matchedCompletely = true;

        while (!indices.empty()) {
            Index index = indices.front();
            indices.pop_front();

            const size_t nodeIdx = index.nodeIdx;
            const size_t patternIdx = index.patternIdx;
            const OpCode& code = patterns.codes[patternIdx];

            if (nodes[nodeIdx].op == code) {
                // op matched, now check all the parent ops
                // std::printf("Checking nodeIdx: %zu\n", nodeIdx);

                const Range& opCodeParentRange = patterns.parentRange[patternIdx];
                const Range& edgeParentRange = getRangeEnd(edges, nodes[nodeIdx].id);

                const size_t opCodeParentLen = opCodeParentRange.size();
                const size_t edgeParentLen = edgeParentRange.size();

                if (opCodeParentLen > edgeParentLen) {
                    // can never match
                    matchedCompletely = false;
                    break;
                }

                if (strict && opCodeParentLen != edgeParentLen) {
                    // if strict,
                    // then all the parent must match
                    matchedCompletely = false;
                    break;
                }

                // actually check if they match
                bool multiMatchPossible = false;
                std::map<int, int> patternParentOpCodeDistribution;
                std::map<int, int> edgeParentOpCodeDistribution;

                for (size_t opIdx = opCodeParentRange.start; opIdx < opCodeParentRange.end; opIdx++) {
                    const OpCode& code = patterns.codes[opIdx];
                    patternParentOpCodeDistribution[code.op] += 1;

                    if (patternParentOpCodeDistribution[code.op] > 1) {
                        multiMatchPossible = true;
                    }
                }

                for (size_t edgeIdx = edgeParentRange.start; edgeIdx < edgeParentRange.end; edgeIdx++) {
                    const OpCode& code = edges[edgeIdx].startOp;

                    edgeParentOpCodeDistribution[code.op] += 1;

                    if (patternParentOpCodeDistribution.count(code.op) && edgeParentOpCodeDistribution[code.op] > 1) {
                        multiMatchPossible = true;
                    }
                }

                // all the distribution values MUST be 0 or else, it's not a match
                bool matchFailed = false;

                for (const auto& [op, count]: patternParentOpCodeDistribution) {
                    if (count > edgeParentOpCodeDistribution[op]) {
                        matchFailed = true;
                        break;
                    }
                }

                if (matchFailed) {
                    matchedCompletely = false;
                    break;
                }

                if (!multiMatchPossible) {
                    //  this node is a match
                    // std::printf("Match Found, nodeId: %d op: %d\n", nodes[nodeIdx].id.id, nodes[nodeIdx].op.op);
                    matchedNodeIndices.emplace_back(nodeIdx);

                    for (size_t opIdx = opCodeParentRange.start; opIdx < opCodeParentRange.end; opIdx++) {
                        // find the matching parent for this op code

                        for (size_t edgeIdx = edgeParentRange.start; edgeIdx < edgeParentRange.end; edgeIdx++) {
                            if (edges[edgeIdx].startOp == patterns.codes[opIdx]) {
                                indices.emplace_back(opIdx, edges[edgeIdx].startIdx);
                            }
                        }
                    }
                } else {
                    // this node is a match
                    // AND, parents need to be searched in combinatorics
                    // std::printf("multi matching parents for nodeId: %d, op: %d\n", nodes[nodeIdx].id.id, nodes[nodeIdx].op.op);
                    matchedNodeIndices.emplace_back(nodeIdx);

                    // combinations for multi match
                    std::deque<Index> nextIndices;

                    // todo: maybe this can be cached
                    // all the existing paths need to be checked as well
                    nextIndices.insert(nextIndices.end(), indices.begin(), indices.end());

                    // ops which can be mapped to one edge directly
                    for (const auto& [opCode, patternCount]: patternParentOpCodeDistribution) {
                        const OpCode op(opCode);

                        const int edgeCount = edgeParentOpCodeDistribution[opCode];

                        if (patternCount == 1 && edgeCount == 1) {
                            // find the edge
                            size_t opEdgeIdx;

                            // this computation is already being performed and maybe cached
                            for (size_t edgeIdx = edgeParentRange.start; edgeIdx < edgeParentRange.end; edgeIdx++) {
                                if (op == edges[edgeIdx].startOp) {
                                    opEdgeIdx = edgeIdx;
                                    break;
                                }
                            }

                            // find the pattern
                            size_t opPatternIdx;
                            for (size_t opIdx = opCodeParentRange.start; opIdx < opCodeParentRange.end; opIdx++) {
                                if (op == patterns.codes[opIdx].op) {
                                    opPatternIdx = opIdx;
                                    break;
                                }
                            }

                            // push into the index
                            nextIndices.emplace_back(opPatternIdx, edges[opEdgeIdx].startIdx);
                        }
                    }

                    std::vector<std::deque<Index>> nextWorkingIndices;
                    std::vector<std::deque<Index>> tmpNextWorkingIndices;

                    nextWorkingIndices.emplace_back(nextIndices);

                    // ops which can be mapped to more than one edge
                    for (const auto& [opCode, patternCount]: patternParentOpCodeDistribution) {
                        const OpCode op(opCode);

                        const int edgeCount = edgeParentOpCodeDistribution[opCode];

                        if (patternCount == 1 && edgeCount == 1) {
                            // already handeled cases
                            continue;
                        }

                        // get the combinations
                        // all the edges with this opCode
                        std::vector<size_t> matchingNodes;
                        std::vector<size_t> matchingPatterns;

                        matchingNodes.reserve(edgeCount);
                        matchingPatterns.reserve(patternCount);

                        for (size_t edgeIdx = edgeParentRange.start; edgeIdx < edgeParentRange.end; edgeIdx++) {
                            if (edges[edgeIdx].startOp == op) {
                                matchingNodes.push_back(edges[edgeIdx].startIdx);
                            }
                        }

                        for (size_t opIdx = opCodeParentRange.start; opIdx < opCodeParentRange.end; opIdx++) {
                            if (patterns.codes[opIdx] == op) {
                                matchingPatterns.push_back(opIdx);
                            }
                        }

                        std::vector<std::vector<Index>> combinations;

                        generateCombinations(matchingPatterns, matchingNodes, combinations);

                        // mix these combinations into all possible nextWorkingIndices
                        for (std::vector<Index>& combination: combinations) {
                            for (std::deque<Index>& workingIndices: nextWorkingIndices) {
                                std::deque<Index> combinedIndices;

                                combinedIndices.insert(combinedIndices.end(), workingIndices.begin(), workingIndices.end());
                                combinedIndices.insert(combinedIndices.end(), combination.begin(), combination.end());

                                tmpNextWorkingIndices.emplace_back(combinedIndices);
                            }
                        }

                        nextWorkingIndices.clear();
                        nextWorkingIndices.insert(nextWorkingIndices.end(), tmpNextWorkingIndices.begin(), tmpNextWorkingIndices.end());
                        tmpNextWorkingIndices.clear();
                    }

                    // for (const auto& comb: nextWorkingIndices) {
                    //     for (const Index& index: comb) {
                    //         std::printf("(%zu, %zu)", index.patternIdx, index.nodeIdx);
                    //     }
                    //     std::printf("\n----------------------------------\n");
                    // }

                    std::deque<Index>& nextWorkingIndicesSliver = nextWorkingIndices.back();

                    // indices already added to the queue
                    // So, it needs to be cleared now
                    indices.clear();
                    indices.insert(indices.end(), nextWorkingIndicesSliver.begin(), nextWorkingIndicesSliver.end());

                    nextWorkingIndices.pop_back();

                    for (std::deque<Index>& nwi : nextWorkingIndices) {
                        workingIndices.emplace_back(matchedNodeIndices, nwi);
                    }
                }
            } else {
                matchedCompletely = false;
                break;
            }
        }

        if (matchedCompletely) {
            // print the current set of indices
            // the indices are being repeated in the output
            // check why

            assert(indices.empty());

            std::vector<NodeId> matchedNodeIds;

            for (size_t matchedNodeIndex: matchedNodeIndices) {
                matchedNodeIds.emplace_back(nodes[matchedNodeIndex].id.id);
            }

            matchedNodesIds.push_back(matchedNodeIds);
        }
    }

    // std::printf("Completed\n");
}

// PUBLIC APIs
PatternGraph* PatternGraph::newGraph() {
    return new PatternGraphImpl();
}

void PatternGraph::deleteGraph(PatternGraph* pg) {
    delete reinterpret_cast<PatternGraphImpl*>(pg);
}

void findPatterns(const std::vector<int>& nodeIds, const std::vector<int>& nodeOps,
                  const std::vector<size_t>& edgeStartIndices, const std::vector<size_t>& edgeEndIndices,
                  const PatternGraph& patternGraph,
                  std::vector<std::vector<int>>& matchedNodeIdsOut) {

    const PatternGraphImpl& patterns = reinterpret_cast<const PatternGraphImpl&>(patternGraph);

    // the buffer to store nodeId to nodeIdx mapping
    std::vector<ssize_t> nodeIndices;
    nodeIndices.reserve(nodeIds.size());

    // the actual nodes that need to be searched
    std::vector<Node> nodes;

    assert(nodeIds.size() == nodeOps.size());
    assert(edgeStartIndices.size() == edgeEndIndices.size());

    for (size_t nodeIdx = 0; nodeIdx < nodeIds.size(); nodeIdx++) {
        // if this operation belongs to one of the
        // pattern ops, select this
        OpCode nodeOp(nodeOps[nodeIdx]);

        if (patterns.hasOp(nodeOp)) {
            // placing the index in which the nodeId can be found
            nodeIndices.emplace_back(nodes.size());
            nodes.emplace_back(nodeIds[nodeIdx], nodeOps[nodeIdx]);
        } else {
            nodeIndices.emplace_back(-1);
        }
    }

    std::vector<Edge> edges;

    for (size_t edgeIdx = 0; edgeIdx < edgeStartIndices.size(); edgeIdx++) {
        NodeId edgeStartId(nodeIds[edgeStartIndices[edgeIdx]]);
        OpCode edgeStartOp(nodeOps[edgeStartIndices[edgeIdx]]);
        size_t edgeStartIdx(nodeIndices[edgeStartIndices[edgeIdx]]);

        NodeId edgeEndId(nodeIds[edgeEndIndices[edgeIdx]]);
        OpCode edgeEndOp(nodeOps[edgeEndIndices[edgeIdx]]);
        size_t edgeEndIdx(nodeIndices[edgeEndIndices[edgeIdx]]);

        // only create edges which make sense
        if (patterns.hasOp(edgeStartOp) && patterns.hasOp(edgeEndOp)) {
            edges.emplace_back(edgeStartId.id, edgeEndId.id,
                               edgeStartOp.op, edgeEndOp.op,
                               edgeStartIdx, edgeEndIdx);
        }
    }

    std::vector<size_t> possibleEndPoints;

    for (size_t nodeIdx = 0; nodeIdx < nodes.size(); nodeIdx++) {
        if (nodes[nodeIdx].op == patterns.codes[0]) {
            possibleEndPoints.push_back(nodeIdx);
        }
    }

    sort<Edge, comp_edges_end>(edges);

    // print_edges(edges);

    std::vector<std::vector<NodeId>> matchedNodeIds;

    findPatterns(nodes, possibleEndPoints, edges, patterns, matchedNodeIds);

    for (const auto& matchedNodeIdsEl: matchedNodeIds) {
        std::vector<int> rawIds;

        for (const auto& matchedNodeId: matchedNodeIdsEl) {
            rawIds.push_back(matchedNodeId.id);
        }

        matchedNodeIdsOut.push_back(rawIds);
    }
}

} // namespace expedera

/*
// testing
int main() {
    using namespace expedera;

    std::vector<Node> nodes;
    std::vector<Edge> adjList;

    // id, op
    nodes.emplace_back(1, 0);
    nodes.emplace_back(2, 1);
    nodes.emplace_back(3, 2);
    nodes.emplace_back(4, 1);
    nodes.emplace_back(5, 2);
    nodes.emplace_back(6, 1);
    nodes.emplace_back(7, 2);
    nodes.emplace_back(8, 1);
    nodes.emplace_back(9, 1);
    nodes.emplace_back(10, 0);
    nodes.emplace_back(11, 3);
    nodes.emplace_back(12, 5);
    nodes.emplace_back(13, 4);

    // revision
    nodes.emplace_back(14, 6);
    nodes.emplace_back(15, 7);
    nodes.emplace_back(16, 6);
    nodes.emplace_back(17, 7);

    // assert position w.r.t index
    // needed for edges
    // I'm just being lazy
    for (size_t idx = 0; idx < nodes.size(); idx++) {
        assert(nodes[idx].id.id == idx + 1);
    }

    // startId, endId, startOp, endOp
    adjList.emplace_back(3, 11, 1, 3);
    adjList.emplace_back(11, 12, 3, 5);
    adjList.emplace_back(1, 2, 0, 1);
    adjList.emplace_back(2, 3, 1, 2);
    adjList.emplace_back(2, 5, 1, 2);
    adjList.emplace_back(2, 4, 1, 1);
    adjList.emplace_back(3, 6, 2, 1);
    adjList.emplace_back(4, 7, 1, 2);
    adjList.emplace_back(5, 8, 2, 1);
    adjList.emplace_back(6, 10, 1, 0);
    adjList.emplace_back(7, 9, 2, 1);
    adjList.emplace_back(8, 10, 1, 0);
    adjList.emplace_back(9, 10, 1, 0);
    adjList.emplace_back(12, 13, 5, 4);
    adjList.emplace_back(10, 13, 0, 4);

    // revision
    adjList.emplace_back(5, 14, 2, 6);
    adjList.emplace_back(14, 15, 6, 7);
    adjList.emplace_back(8, 15, 1, 7);
    adjList.emplace_back(15, 16, 7, 6);
    adjList.emplace_back(10, 17, 0, 7);
    adjList.emplace_back(16, 17, 6, 7);
    adjList.emplace_back(17, 13, 7, 4);

    std::printf("---------------------------\n");
    print_edges(adjList);
    std::printf("---------------------------\n");

    PatternGraphImpl g;

    size_t add_idx = g.addParent(4);
    g.setChildIdx(add_idx);
    size_t min_idx = g.addParent(7);
    g.setChildIdx(min_idx);
    size_t mul_idx = g.addParent(0);
    size_t max_idx = g.addParent(6);
    g.setChildIdx(max_idx);
    size_t min_idx1 = g.addParent(7);
    g.setChildIdx(min_idx1);
    size_t sub_idx1 = g.addParent(1);
    size_t max_idx1 = g.addParent(6);

    // size_t add_idx = g.addParent(4);
    // g.setChildIdx(add_idx);
    // size_t mul_idx = g.addParent(0);
    // size_t abs_idx = g.addParent(5);
    // g.setChildIdx(abs_idx);
    // size_t max0_idx = g.addParent(3);

    sort<Edge, comp_edges_end>(adjList);

    std::printf("---------------------------\n");
    print_edges(adjList);
    std::printf("---------------------------\n");

    // assuming all end points are possible
    std::vector<size_t> possibleEndPoints;

    for (size_t idx = 0; idx < nodes.size(); idx++) {
        // most basic of filters for pruning the nodes
        // only search for indices which has the same
        // matching end pattern
        if (nodes[idx].op == g.codes[0]) {
            possibleEndPoints.emplace_back(idx);
        }
    }

    findPatterns(nodes, possibleEndPoints, adjList, g);
}
*/
