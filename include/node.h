#ifndef NODE_H
#define NODE_H

#include <memory>

#include "attrs.h"
#include "list.h"
#include "node_data.h"

class List;

typedef enum{
    INITIALIZER,
    CONV,
    BATCHNORMALIZATION,
    MAXPOOL,
    GLOBALAVERAGEPOOL,
    RELU,
    CLIP, 
    ADD,
    SUB
} OPCODE;

class Node {

public:
    // Constructor
    Node();

    Node(int opcode);

    Node(int opcode, List* attrs);

    // Copy Constructor
    Node(const Node& other);

    // Destructor
    ~Node();

    // Assignment operator
    Node& operator=(const Node& other) = delete;

    int getId() const;

    int getOpcode() const;
    
    void setOpcode(int opcode);

    bool operator==(const Node& other) const {
        return getId() == other.getId();
    }

private:
    static int nextId;
    int id;
    OPCODE opcode;
    List* attrs;

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

extern "C" {
    Node* new_node_from_opcode(int opcode);

    void node_from_node(Node* source);

    int get_id(Node* obj);

    int get_opcode(Node* obj);

    Node* new_node_from_all(int opcode, List* attrs);

    void del_node(bool debug, Node* node);
}

#endif // Node_H
