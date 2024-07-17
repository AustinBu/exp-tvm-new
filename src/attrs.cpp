#include "../include/attrs.h"

Attrs::Attrs() {}

Attrs::Attrs(const char* name, int type, int* in_ints, int intssize)
    : type(TYPE(type)), ints(in_ints), intssize(intssize) {
        this->name = strdup(name); // Copy the string
    }

Attrs::Attrs(char** name, int type, int i)
    : name(*name), type(TYPE(type)), i(i) {}

extern "C" {
    Attrs* new_attrs_ints(const char* name, int type, int* ints, int intssize)
    { return new Attrs(name, type, ints, intssize); }

    Attrs* new_attrs_i(char** name, int type, int i)
    { return new Attrs(name, type, i); }
}
