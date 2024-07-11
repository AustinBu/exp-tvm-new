#ifndef RELU_H
#define RELU_H

class ReLU {
private:
    int* input;
    int* output;
    int size;

public:
    ReLU(int size);

    void activate();

    void print() const;
};

#endif // RELU_H
