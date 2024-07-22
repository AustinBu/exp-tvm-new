from python.base import *
from python.opmap import *
from ctypes import *
import atexit

map = opmap
debug = False

class Graph:
    def __init__(self):
        self.layers = []
        self.edges = []
        self.attrs = []
        atexit.register(self.cleanup)

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
    
    def new_node_from_all(self, opcode, attrs, attrsize):
        self.layers.append(exp.new_node_from_all(opcode, attrs, attrsize))
        return self.layers[-1]

    def new_edge(self, start, end):
        self.edges.append(exp.new_edge(start, end))
        print("Edge: ", self.edges[-1].contents.id)
        return self.edges[-1]
    
    def get_edge(self, edge):
        return map[edge[0].start[0].opcode], map[edge[0].end[0].opcode]
    
    def new_attrs(self, name, type, ints=None, i=None):
        attr = 0
        if i != None:
            attr = exp.new_attrs_i(
                create_string_buffer(name), 
                type,
                i
            )
        else:
            ints = self.handleInts(ints)
            attr = exp.new_attrs_ints(
                create_string_buffer(name), 
                type,
                ints,
                len(ints)
            )
        self.attrs.append(attr)
        return attr
    
    def handleInts(self, ints):
        return (c_int * len(ints))(*ints)
        # ints.ctypes.data_as(POINTER(c_int))

    def del_attrs(self, attrs):
        exp.del_attrs(debug, attrs)

    def del_node(self, node):
        exp.del_node(debug, node)

    def del_edge(self, edge):
        exp.del_edge(debug, edge)

    def cleanup(self):
        for n in self.layers:
            self.del_node(n)
        for e in self.edges:
            self.del_edge(e)
        for a in self.attrs:
            self.del_attrs(a)

