#include "../include/args.h"
#include "../include/attrs.h"

Args::Args() {}

Args::Args(int* input)
    : int_input(input) {}

extern "C" {
    Args* new_args(int* input) 
    { return new Args(input); }
}
