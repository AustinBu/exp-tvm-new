#ifndef ARGS_H
#define ARGS_H

#include <iostream>
#include "attrs.h"

class Args {
public:
    Args();

    Args(int* input);

private:
    int* int_input;
};

#endif // EDGE_H