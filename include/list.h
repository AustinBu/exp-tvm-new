#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "attrs.h"

typedef enum {
    ATTRS,
    NODE,
    EDGE,
} LISTTYPE;

class List {
public:
    List();

    List(void* data, int size, int type);

    ~List();

    const int getSize() const;
    
    const Attrs* getAttr() const;

private:
    void* data;
    int size;
    LISTTYPE type;
};

extern "C" {
    List* new_list(void* data, int size, int type);

    void del_list(bool debug, List* list);
}

#endif // LIST_H