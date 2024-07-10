#include "../include/clip_obj.h"
#include "../include/object.h"

ClipObject::ClipObject() {}

ClipObject::ClipObject(Object source)
    : Object(6) {
    if (source.opcode == 5) {
        max = INT_MAX;
        min = 0;
    }
}

extern "C" {
    ClipObject* Clip() { return new ClipObject(); }
    ClipObject* toClip(Object source) { return new ClipObject(source); }
}