from . import base
from . import namemap

exp = base.exp
map = namemap.map

class Layer:
    def __init__(self):
        self.layers = []

    def __str__(self):
        s = "Layers["
        for l in self.layers:
            if l.contents.opcode == 5:
                s += "Relu()"
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

