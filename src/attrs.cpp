#include "../include/attrs.h"

Attrs::Attrs() {}

Attrs::Attrs(char** name, int type, int* in_ints, int intssize)
    : name(*name), type(TYPE(type)) {
        ints = std::vector<int>(in_ints, in_ints + intssize);
    }

Attrs::Attrs(char** name, int type, int i)
    : name(*name), type(TYPE(type)), i(i) {}

extern "C" {
    Attrs* new_attrs_ints(char** name, int type, int* ints, int intssize)
    { return new Attrs(name, type, ints, intssize); }

    Attrs* new_attrs_i(char** name, int type, int i)
    { return new Attrs(name, type, i); }
}
