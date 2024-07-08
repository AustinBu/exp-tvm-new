#include "object.h"

Object::Object(int op, int* a, int* in, int* out, int nArgs, int nInputs, int nOutputs)
    : opcode(op), args(a), input(in), output(out), numArgs(nArgs), numInputs(nInputs), numOutputs(nOutputs) {}

int Object::getOpcode() const { return opcode; }
int* Object::getArgs() const { return args; }
int* Object::getInput() const { return input; }
int* Object::getOutput() const { return output; }
int Object::getNumArgs() const { return numArgs; }
int Object::getNumInputs() const { return numInputs; }
int Object::getNumOutputs() const { return numOutputs; }

void Object::setOpcode(int op) { opcode = op; }
void Object::setArgs(int* a) { args = a; }
void Object::setInput(int* in) { input = in; }
void Object::setOutput(int* out) { output = out; }
void Object::setNumArgs(int nArgs) { numArgs = nArgs; }
void Object::setNumInputs(int nInputs) { numInputs = nInputs; }
void Object::setNumOutputs(int nOutputs) { numOutputs = nOutputs; }

void Object::print() const {
    std::cout << "Opcode: " << opcode << std::endl;
    std::cout << "Args: ";
    for (int i = 0; i < numArgs; ++i) {
        std::cout << args[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Input: ";
    for (int i = 0; i < numInputs; ++i) {
        std::cout << input[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Output: ";
    for (int i = 0; i < numOutputs; ++i) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;
}
