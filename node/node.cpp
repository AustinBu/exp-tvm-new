#include "../include/node.h"

Node::Node() {}

Node::Node(int opcode)
    : opcode(opcode) {}

Node::Node(const Node& source)
    : opcode(0)
{
    if (source.opcode == 5)
    {
        opcode = 6;
    }
}

int Node::getOpcode() const { return opcode; }

void Node::setOpcode(int newOpcode) {
    opcode = newOpcode;
}

extern "C" {
    Node* new_node_from_opcode(int opcode) { return new Node(opcode); }

    void node_from_node(Node* source) {
        if (source->getOpcode() == 5) {
            source->setOpcode(6);
        }
    }

    int get_opcode(Node* obj) { return obj->getOpcode(); }
}