#ifndef CLIPOBJECT_H
#define CLIPOBJECT_H

#include <iostream>
#include "object.h"

class ClipObject : public Object {
public:

    // Constructor
    ClipObject();
    ClipObject(const Object &source);
    ClipObject(const ClipObject &source);
    ClipObject(Object input, Object output, int min, int max);

    Object input;
    Object output;
    int min;
    int max;
    
};

#endif // RELUOBJECT_H