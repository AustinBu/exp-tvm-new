from . import base
from . import opmap
from ctypes import *

exp = base.exp
map = opmap.opmap

class Layer:
    def __init__(self):
        self.layers = []

    def __str__(self):
        s = "Layers["
        for l in self.layers:
            # breakpoint()
            if l.contents.opcode == 5:
                s += "Relu(), "
            elif l.contents.opcode == 1:
                s += "Conv(), "
        s += "]"
        return s

    def relu(self):
        self.layers.append(exp.new_node_from_opcode(5))
        return self.layers[-1]
    
    def new_node(self, opcode):
        self.layers.append(exp.new_node_from_opcode(opcode))
        return self.layers[-1]

    def new_edge(self, start, end):
        return exp.new_edge(start, end)
    
    def get_edge(self, edge):
        return map[edge.contents.start.contents.opcode], map[edge.contents.end.contents.opcode]
    
    def new_attrs(self, name, type, ints):
        return exp.new_attrs_ints(
                            create_string_buffer(name), 
                            type,
                            ints.ctypes.data_as(POINTER(c_int)),
                            len(ints))
    
    def new_node_all(self, opcode, attrs, attrsize):
        return exp.new_node_from_all(opcode, attrs, attrsize)
    
    def del_attrs(self, attrs):
        exp.del_attrs(attrs)

    def del_node(self, node):
        exp.del_node(node)

    def del_edge(self, edge):
        exp.del_edge(edge)

