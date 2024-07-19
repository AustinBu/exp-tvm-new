#include "../include/attrs.h"

Attrs::Attrs() {}

Attrs::Attrs(const char* name, int type, int* in_ints, int intssize)
    : type(TYPE(type)), intssize(intssize) {
        this->name = strdup(name); // Copy the string
        this->ints = new int[intssize];
        std::memcpy(this->ints, in_ints, intssize * sizeof(int));
    }

Attrs::Attrs(const char* name, int type, int i)
    : type(TYPE(type)), i(i) {
        this->name = strdup(name); // Copy the string
    }

Attrs::~Attrs() {
        delete[] name; // Free the copied string
        delete[] ints; // Free the integer array
    }

const char* Attrs::getName() const {
    return name;
}

Attrs* new_attrs_ints(const char* name, int type, int* ints, int intssize)
{ return new Attrs(name, type, ints, intssize); }

Attrs* new_attrs_i(const char* name, int type, int i)
{ return new Attrs(name, type, i); }

void del_attrs(bool debug, Attrs* attrs) {
    if (debug) { std::cout << "Deleting attr: " << attrs->getName() << std::endl; }
    delete attrs;
}
