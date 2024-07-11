#ifndef RELUOBJECT_H
#define RELUOBJECT_H

#include <iostream>
#include "object.h"

class ReluObject : public Object {
public:
    // Constructor
    ReluObject();
    ReluObject(Object input, Object output);

    Object input;
    Object output;
    int get_output() {
        return 1;
    }
    
};

#endif // RELUOBJECT_H