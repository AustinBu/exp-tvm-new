#include "../include/object.h"

Object::Object() {}

Object::Object(int opcode)
    : opcode(opcode) {}

// Object::Object(const Object& source)
//     : opcode(0)
// {
//     if (source.opcode == 5)
//     {
//         opcode = 6;
//     }
// }

extern "C" {
    Object* new_object(int opcode) { return new Object(opcode); }
    // Object* new_object(Object source) { return new Object(source); }
    int get_opcode(Object* obj) { return obj->opcode; }
}