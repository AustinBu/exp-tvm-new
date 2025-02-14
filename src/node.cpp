#include <iostream>

#include "../include/node.h"
#include "../include/attrs.h"


int Node::nextId = 1;

Node::Node() {}

Node::Node(int opcode) : id(generateId()), opcode(OPCODE(opcode)) {}

Node::Node(const Node& source) : id(source.id), opcode(OPCODE(0))
{
    if (source.opcode != 0)
    {
        opcode = OPCODE(source.opcode);
    }
}

Node::~Node() {}

int Node::getId() const { return this->id; }

Node::Node(int opcode, List* in_attrs)
    : id(generateId()), opcode(OPCODE(opcode)) {
        int size = in_attrs->getSize();
        this->attrs = in_attrs;
}

int Node::getOpcode() const { return this->opcode; }

void Node::setOpcode(int newOpcode) {
    opcode = OPCODE(newOpcode);
}

int Node::generateId() {
    return nextId++;
}

Node* new_node_from_opcode(int opcode) { return new Node(opcode); }

void node_from_node(Node* source) {
    // todo: supposed to return a new node pointer?
}

int get_id(Node* obj) { return obj->getId(); }

int get_opcode(Node* obj) { return obj->getOpcode(); }

Node* new_node_from_all(int opcode, List* attrs) 
    { return new Node(opcode, attrs); }

void del_node(bool debug, Node* node) {
    if (debug) { std::cout << "Deleting node: " << node << std::endl; }
    delete node;
}
