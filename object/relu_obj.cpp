#include "../include/relu_obj.h"
#include "../include/object.h"

ReluObject::ReluObject(Object input, Object output)
    : input(input), output(output) {}

ReluObject::ReluObject() 
    : Object(5) {}

extern "C" {
    ReluObject* Relu() { return new ReluObject(); }
}