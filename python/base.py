from ctypes import *

exp = cdll.LoadLibrary('./exp.so')
    
class Attrs(Structure):
    _fields_ = [("name", c_char_p),
                ("type", c_int),
                ("ints", POINTER(c_int)),
                ("i", c_int)]
    
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

exp.new_attrs_ints.argtypes = [POINTER(c_char_p), c_int, POINTER(c_int), c_int]
exp.new_attrs_ints.restype = POINTER(Attrs)
