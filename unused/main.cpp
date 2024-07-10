#include "relu.h"


int main() {
    int values[] = {5, -3, 8, -1, 0, 7};
    int size = sizeof(values);

    ReLU relu(size);
    relu.print(); 

    return 0;
}
