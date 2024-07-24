#include <iostream>

#include "../include/node.h"
#include "../include/attrs.h"


int Node::nextId = 1;

Node::Node():
           data(std::make_shared<NodeData>(generateId(), 0, nullptr)) {}

Node::Node(int opcode):
           data(std::make_shared<NodeData>(generateId(), opcode, nullptr)) {}

Node::Node(int opcode, List* in_attrs):
           data(std::make_shared<NodeData>(generateId(), 0, in_attrs)) {}

Node::Node(const Node& source):
           data(source.data) {}

Node::~Node() {}

int Node::getId() const { return data->id; }

int Node::getOpcode() const { return data->opcode; }

void Node::setOpcode(int newOpcode) {
    data->opcode = newOpcode;
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
