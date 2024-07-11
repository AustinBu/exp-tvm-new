#include "../include/object.h"

Object::Object() {}

Object::Object(int opcode)
    : opcode(opcode) {}

Object::Object(const Object& source)
    : opcode(0)
{
    if (source.opcode == 5)
    {
        opcode = 6;
    }
}

extern "C" {
    Object* new_object_from_opcode(int opcode) { return new Object(opcode); }
    void new_object_from_object(Object* source) {
        if (source->opcode == 5) {
            source->opcode = 6;
        }
    }
    int get_opcode(Object* obj) { return obj->opcode; }
}