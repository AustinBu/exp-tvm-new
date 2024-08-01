#ifndef EXP_PATTERN_FINDER_H
#define EXP_PATTERN_FINDER_H

namespace expedera {

class PatternGraph {
    public:
    static PatternGraph* newGraph();

    static void deleteGraph(PatternGraph* pg);

    // add a parent to the current child
    virtual size_t addParent(const int& code) = 0;

    // set one of the parents as the new child to
    // add more parents
    virtual void setChildIdx(size_t idx) = 0;

    // get the number of elements in the pattern graph
    virtual size_t size() const = 0;
};

void findPatterns(const std::vector<int>& nodeIds, const std::vector<int>& nodeOps,
                  const std::vector<size_t>& edgeStartIdx, const std::vector<size_t>& edgeEndIdx,
                  const PatternGraph& patterns, std::vector<std::vector<int>>& matchedNodeIdsOut);

} // namespace expedera

#endif // EXP_PATTERN_FINDER_H
