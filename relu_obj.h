#ifndef RELUOBJECT_H
#define RELUOBJECT_H

#include "object.h"

class ReluObject : public Object {
public:
    // Constructor
    ReluObject(int* a, int* in, int* out, int nArgs, int nInputs, int nOutputs);
};

#endif // RELUOBJECT_H