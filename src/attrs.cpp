#include "../include/attrs.h"

Attrs::Attrs() {}

Attrs::Attrs(int indtype, int outdtype, int* inshape, int insize, int* outshape, int outsize)
    : inputdtype(TYPE(indtype)), outputdtype(TYPE(outdtype)), inshape(inshape), insize(insize), outshape(outshape), outsize(outsize) {}

extern "C" {
    Attrs* new_attrs(int indtype, int outdtype, int* inshape, int insize, int* outshape, int outsize) 
    { return new Attrs(indtype, outdtype, inshape, insize, outshape, outsize); }
}
