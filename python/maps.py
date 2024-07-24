from python.base import *

opmap = {
    0: "Initializer",
    1: "Conv",
    5: "Relu",
    6: "Clip"
}

opcodemap = {
    "Initializer": 0,
    "Conv": 1, 
    "Relu": 5,
    "Clip": 6
}

attr_to_int_map = {
    Attrs: 1,
    Node: 2,
    Edge: 3
}

int_to_attr_map = {value: key for key, value in attr_to_int_map.items()}
