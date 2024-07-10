#include "../include/clip_obj.h"
#include "../include/object.h"

ClipObject::ClipObject() {}

ClipObject::ClipObject(const Object& source)
    : Object(6)
{
    if (source.opcode == 5)
    {
        max = INT_MAX;
        min = 0;
    }
}

ClipObject::ClipObject(const ClipObject& source)
    : Object(6)
{
    if (source.opcode == 5)
    {
        max = INT_MAX;
        min = 0;
    }
}

extern "C"
{
    ClipObject *Clip() { return new ClipObject(); }
    Object *toClip(ClipObject source)
    {
        std::cout << source.opcode << std::endl;
        auto* res =  new ClipObject(source);
        std::cout << res->opcode << std::endl;
        return res;
    }
}