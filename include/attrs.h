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

    Attrs(char** name, int type, int* ints, int intssize);

    Attrs(char** name, int type, int i);

    ~Attrs() {
        delete name;
    }

    char* getName() {
        return name;
    }

private:
    char* name;
    TYPE type;
    std::vector<int> ints;
    int i;
};

#endif // ATTRS_H