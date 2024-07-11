#include "../include/object.h"

Object::Object() {}

Object::Object(int opcode)
    : opcode(opcode) {}

extern "C" {
    int get_opcode(Object* obj) { return obj->opcode; }
}