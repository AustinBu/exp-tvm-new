#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "attrs.h"

class Node {

public:
    // Constructor
    Node();

    Node(int opcode);

    // Destructor
    ~Node() {
    }

    // Copy Constructor
    Node(const Node& other);

    Node(int opcode, Attrs* attrs, int attrsize);

    // Assignment operator (optional, for best practice)
    Node& operator=(const Node& other) {
        if (this == &other) {
            return *this;
        }

        opcode = other.opcode;
        return *this;
    }

    int getId() const;

    int getOpcode() const;
    void setOpcode(int opcode);

    bool operator==(const Node& other) const {
        return id == other.id;
    }

private:
    static int nextId;
    int id;
    int opcode;
    Attrs* attrs;
    int attrsize;

    static int generateId();
};

namespace std {
    template <>
    struct hash<Node> {
        std::size_t operator()(const Node& node) const {
            return std::hash<int>()(node.getId());
        }
    };
}

#endif // Node_H
