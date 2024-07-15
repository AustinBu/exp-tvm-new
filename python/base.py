from ctypes import *

exp = cdll.LoadLibrary('./exp.so')
    
class Attrs(Structure):
    _fields_ = [("inputdtype", c_int),
                ("outputdtype", c_int),
                ("inshape", POINTER(c_int)),
                ("insize", c_int),
                ("outshape", POINTER(c_int)),
                ("outsize", c_int)]
    
class Node(Structure):
    _fields_ = [("id", c_int),
                ("opcode", c_int),
                ("attrs", POINTER(Attrs))]
    
class Edge(Structure):
    _fields_ = [("start", POINTER(Node)),
                ("end", POINTER(Node))]

exp.new_node_from_opcode.argtypes = [c_int]
exp.new_node_from_opcode.restype = POINTER(Node)
exp.node_from_node.argtypes = [POINTER(Node)]
exp.new_node_from_all.argtypes = [c_int, POINTER(Attrs)]
exp.new_node_from_all.restype = POINTER(Node)

exp.new_edge.argtypes = [POINTER(Node), POINTER(Node)]
exp.new_edge.restype = POINTER(Edge)

exp.get_opcode.argtypes = [POINTER(Node)]
exp.get_opcode.restype = c_int

exp.new_attrs.argtypes = [c_int, c_int, POINTER(c_int), c_int, POINTER(c_int), c_int]
exp.new_attrs.restype = POINTER(Attrs)
