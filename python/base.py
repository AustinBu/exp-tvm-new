from ctypes import *

exp = cdll.LoadLibrary('./exp.so')
    
class Attrs(Structure):
    _fields_ = [("name", c_char_p),
                ("type", c_int),
                ("ints", POINTER(c_int)),
                ("ints_size", c_int),
                ("i", c_int)]
    
class Node(Structure):
    _fields_ = [("id", c_int),
                ("opcode", c_int),
                ("attrs", POINTER(Attrs)),
                ("attrsize", c_int)]
    
class Edge(Structure):
    _fields_ = [("start", POINTER(Node)),
                ("end", POINTER(Node)), 
                ("id", c_int)]

exp.new_node_from_opcode.argtypes = [c_int]
exp.new_node_from_opcode.restype = POINTER(Node)
exp.node_from_node.argtypes = [POINTER(Node)]
exp.new_node_from_all.argtypes = [c_int, POINTER(Attrs), c_int]
exp.new_node_from_all.restype = POINTER(Node)

exp.new_edge.argtypes = [POINTER(Node), POINTER(Node)]
exp.new_edge.restype = POINTER(Edge)

exp.get_opcode.argtypes = [POINTER(Node)]
exp.get_opcode.restype = c_int

exp.new_attrs_ints.argtypes = [c_char_p, c_int, POINTER(c_int), c_int]
exp.new_attrs_ints.restype = POINTER(Attrs)
exp.new_attrs_i.argtypes = [c_char_p, c_int, c_int]
exp.new_attrs_i.restype = POINTER(Attrs)

exp.del_attrs.argtypes = [c_bool, POINTER(Attrs)]
exp.del_node.argtypes = [c_bool, POINTER(Node)]
exp.del_edge.argtypes = [c_bool, POINTER(Edge)]

exp.edge_get_id.argtypes = [POINTER(Edge)]
exp.edge_get_id.restype = c_int