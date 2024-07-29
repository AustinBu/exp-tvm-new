#include "../include/list.h"
#include "../include/attrs.h"

List::List() {}

List::List(void* data, int size, int type)
    : size(size), type(LISTTYPE(type)) {
        if (type == 0) {
            Attrs* attr = static_cast<Attrs*>(data);
            this->data = attr;
        }
    }

List::~List() {}

const int List::getSize() const {
    return size;
}

const Attrs* List::getAttr() const {
    return static_cast<Attrs*>(data);
}

List* new_list(void* data, int size, int type)
{ return new List(data, size, type); }

void del_list(bool debug, List* list) {
    if (debug) { std::cout << "Deleting list: " << list << std::endl; }
    delete list;
}