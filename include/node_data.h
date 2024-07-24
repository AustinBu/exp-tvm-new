#ifndef NODE_DATA_H
#define NODE_DATA_H

#include "attrs.h"
#include "list.h"

struct NodeData {
    int id;
    int opcode;
    List* attrs;

    NodeData(int id, int opcode, List* attrs):
             id(id),
             opcode(opcode),
             attrs(attrs) {}
};

#endif // NODE_DATA_H
