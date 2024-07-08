#include "relu_obj.h"

int main() {
    int args[] = {10, 20};
    int input[] = {30, 40};
    int output[] = {50, 60};

    ReluObject relu(args, input, output, 2, 2, 2);
    relu.print();

    return 0;
}
