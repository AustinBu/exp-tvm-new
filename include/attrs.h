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

    Attrs(const char* name, int type, int* ints, int intssize);

    Attrs(char** name, int type, int i);

    ~Attrs() {
        delete[] name; // Free the copied string
        delete[] ints; // Free the integer array
    }

    const char* getName() const {
        return name;
    }

private:
    const char* name;
    TYPE type;
    int* ints;
    int intssize;
    int i=0;
};

#endif // ATTRS_H