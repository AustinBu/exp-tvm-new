from python.base import *

opmap = {
    0: "Initializer",
    1: "Conv",
    2: "BatchNormalization",
    3: "MaxPool",
    4: "GlobalAveragePool",
    5: "Relu",
    6: "Clip", 
    7: "Add"
}

opcodemap = {
    "Initializer": 0,
    "Conv": 1, 
    "BatchNormalization": 2,
    "MaxPool": 3,
    "GlobalAveragePool": 4,
    "Relu": 5,
    "Clip": 6, 
    "Add": 7
}

# attr_to_int_map = {
#     Attrs: 1,
#     Node: 2,
#     Edge: 3
# }

# int_to_attr_map = {value: key for key, value in attr_to_int_map.items()}

def get_op_from_code(opcode):
    return opmap[opcode]