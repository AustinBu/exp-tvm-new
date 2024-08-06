#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "attrs.h"
#include "edge.h"

class List {
public:
    List();

    List(void* data, int size, int type);

    ~List();

    int getSize();
    
    Attrs* getAttr();

    Edge* getEdge();

private:
    void* data;
    int size;
    DATATYPE type;
};

extern "C" {
    List* new_list(void* data, int size, int type);

    void del_list(bool debug, List* list);
}

#endif // LIST_H