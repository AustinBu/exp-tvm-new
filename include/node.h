#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {

public:
    // Constructor
    Node();

    Node(int opcode);

    // Destructor
    ~Node() {}

    // Copy Constructor
    Node(const Node& other);

    // Assignment operator (optional, for best practice)
    Node& operator=(const Node& other) {
        if (this == &other) {
            return *this;
        }

        opcode = other.opcode;
        return *this;
    }

    int getOpcode() const;
    void setOpcode(int opcode);

private:
    int opcode = 0;
};

#endif // Node_H
