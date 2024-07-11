#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

class Object {

public:
    int opcode = 0;
    
    // Constructor
    Object();

    Object(int opcode);

    // Destructor
    ~Object() {}

    // Copy Constructor
    Object(const Object& other);

    // Assignment operator (optional, for best practice)
    Object& operator=(const Object& other) {
        if (this == &other) {
            return *this;
        }

        opcode = other.opcode;
        return *this;
    }

};

#endif // OBJECT_H
