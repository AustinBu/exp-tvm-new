#ifndef ATTRS_H
#define ATTRS_H

#include <iostream>

typedef enum {
    CHAR,
    INT,
    FLOAT,
    DOUBLE
} DATATYPE;

class Attrs {
public:
    Attrs();

    Attrs(const char* name, int type, int* ints, int intssize);

    Attrs(const char* name, int type, int i);

    ~Attrs();

    const char* getName() const;

private:
    const char* name;
    DATATYPE type;
    int* ints;
    int intssize;
    int i;
};

extern "C" {
    Attrs* new_attrs_ints(const char* name, int type, int* ints, int intssize);

    Attrs* new_attrs_i(const char* name, int type, int i);

    void del_attrs(bool debug, Attrs* attrs);
}

#endif // ATTRS_H