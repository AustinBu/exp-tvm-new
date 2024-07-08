#include "relu_obj.h"

ReluObject::ReluObject(int* a, int* in, int* out, int nArgs, int nInputs, int nOutputs)
    : Object(5, a, in, out, nArgs, nInputs, nOutputs) {}