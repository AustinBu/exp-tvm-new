#include "../include/list.h"
#include "../include/attrs.h"
#include "../include/edge.h"

List::List() {}

List::List(void* data, int size, int type)
    : size(size), type(DATATYPE(type)) {
        // if (this->type == ATTRS) {
        //     Attrs* attrs = static_cast<Attrs*>(data);
        //     this->data = attrs;
        // } else if (this->type == EDGE) {
        //     Edge* edges = static_cast<Edge*>(data);
        //     this->data = edges;
        // }
        this->data = data;
    }

List::~List() {
    if (this->type == INT) {
        int* ints = static_cast<int*>(data);
        delete[] ints;
    }
}

int List::getSize() {
    return size;
}

Attrs* List::getAttr() {
    return static_cast<Attrs*>(data);
}

Edge* List::getEdge() {
    return static_cast<Edge*>(data);
}

List* new_list(void* data, int size, int type)
{ return new List(data, size, type); }

void del_list(bool debug, List* list) {
    if (debug) { std::cout << "Deleting list: " << list << std::endl; }
    delete list;
}