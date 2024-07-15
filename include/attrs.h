#ifndef ATTRS_H
#define ATTRS_H

#include <iostream>

typedef enum {
    CHAR,
    INT,
    FLOAT,
    DOUBLE
} TYPE;

class Attrs {
public:
    Attrs();

    Attrs(int indtype, int outdtype, int* inshape, int insize, int* outshape, int outsize);

private:
    TYPE inputdtype;
    TYPE outputdtype;
    int* inshape;
    int insize;
    int* outshape;
    int outsize;
};

#endif // EDGE_H