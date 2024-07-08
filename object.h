#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

class Object {
private:
    int opcode;
    int* args;
    int* input;
    int* output;
    int numArgs;
    int numInputs;
    int numOutputs;

public:
    // Constructor
    Object(int op, int* a, int* in, int* out, int nArgs, int nInputs, int nOutputs);

    int getOpcode() const;
    int* getArgs() const;
    int* getInput() const;
    int* getOutput() const;
    int getNumArgs() const;
    int getNumInputs() const;
    int getNumOutputs() const;

    void setOpcode(int op);
    void setArgs(int* a);
    void setInput(int* in);
    void setOutput(int* out);
    void setNumArgs(int nArgs);
    void setNumInputs(int nInputs);
    void setNumOutputs(int nOutputs);

    void print() const;
};

#endif // OBJECT_H
