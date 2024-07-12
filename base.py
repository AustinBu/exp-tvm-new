from ctypes import *

exp = cdll.LoadLibrary('./exp.so')

class Node(Structure):
    _fields_ = [("opcode", c_int)]

class Edge(Structure):
    _fields_ = [("start", POINTER(Node)),
                ("end", POINTER(Node))]

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

exp.new_node_from_opcode.argtypes = [c_int]
exp.new_node_from_opcode.restype = POINTER(Node)
exp.node_from_node.argtypes = [POINTER(Node)]

exp.new_edge.argtypes = [POINTER(Node), POINTER(Node)]
exp.new_edge.restype = POINTER(Edge)

exp.get_opcode.argtypes = [POINTER(Node)]
exp.get_opcode.restype = c_int
