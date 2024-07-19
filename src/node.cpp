#include "../include/node.h"
#include "../include/attrs.h"
#include <iostream>

int Node::nextId = 1;

Node::Node() : id(generateId()) {}

Node::Node(int opcode) : id(generateId()), opcode(opcode) {}

Node::Node(const Node& source) : id(source.id), opcode(0)
{
    if (source.opcode == 5)
    {
        opcode = 6;
    }
}

Node::~Node() {}

int Node::getId() const { return id; }

Node::Node(int opcode, Attrs* in_attrs, int attrsize)
    : opcode(opcode), attrs(in_attrs), attrsize(attrsize) {
        this->attrs = new Attrs[attrsize];
        std::memcpy(this->attrs, in_attrs, attrsize * sizeof(Attrs));
}

int Node::getOpcode() const { return opcode; }

void Node::setOpcode(int newOpcode) {
    opcode = newOpcode;
}

int Node::generateId() {
    return nextId++;
}

Node* new_node_from_opcode(int opcode) { return new Node(opcode); }

void node_from_node(Node* source) {
    if (source->getOpcode() == 5) {
        source->setOpcode(6);
    }
}

int get_id(Node* obj) { return obj->getId(); }

int get_opcode(Node* obj) { return obj->getOpcode(); }

Node* new_node_from_all(int opcode, Attrs* attrs, int attrsize) 
    { return new Node(opcode, attrs, attrsize); }

void del_node(Node* node) {
    std::cout << "Deleting node: " << node << std::endl;
    delete node;
}
