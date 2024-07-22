from ctypes import *

exp = cdll.LoadLibrary('./exp.so')


class Attrs(Structure):
    _fields_ = [("name", c_char_p),
                ("type", c_int),
                ("ints", POINTER(c_int)),
                ("ints_size", c_int),
                ("i", c_int)]
    
class List(Structure):
    _fields_ = [("data", c_void_p),
                ("size", c_int),
                ("type", c_int)]
    def getData(self):
        if self.type == 0:
            return cast(self.data, POINTER(Attrs))

class Node(Structure):
    _fields_ = [("id", c_int),
                ("opcode", c_int),
                ("attrs", POINTER(List))]
    def getData(self):
        if self.attrs[0].size == 0:
            return 0
        ret = []
        data = self.attrs[0].getData()
        for i in range(self.attrs[0].size):
            ret.append(data[i])
        return ret
    
class Edge(Structure):
    _fields_ = [("start", POINTER(Node)),
                ("end", POINTER(Node)), 
                ("id", c_int)]
    def getStartOp(self):
        # Redirect attribute access to the first object in the list
        return self.start[0].opcode
    def getEndOp(self):
        # Redirect attribute access to the first object in the list
        return self.end[0].opcode

exp.new_node_from_opcode.argtypes = [c_int]
exp.new_node_from_opcode.restype = POINTER(Node)
exp.node_from_node.argtypes = [POINTER(Node)]
exp.new_node_from_all.argtypes = [c_int, POINTER(List)]
exp.new_node_from_all.restype = POINTER(Node)

exp.new_edge.argtypes = [POINTER(Node), POINTER(Node)]
exp.new_edge.restype = POINTER(Edge)
exp.edge_get_id.argtypes = [POINTER(Edge)]
exp.edge_get_id.restype = c_int

exp.get_opcode.argtypes = [POINTER(Node)]
exp.get_opcode.restype = c_int

exp.new_attrs_ints.argtypes = [c_char_p, c_int, POINTER(c_int), c_int]
exp.new_attrs_ints.restype = POINTER(Attrs)
exp.new_attrs_i.argtypes = [c_char_p, c_int, c_int]
exp.new_attrs_i.restype = POINTER(Attrs)

exp.new_list.argtypes = [c_void_p, c_int, c_int]
exp.new_list.restype = POINTER(List)

exp.del_attrs.argtypes = [c_bool, POINTER(Attrs)]
exp.del_node.argtypes = [c_bool, POINTER(Node)]
exp.del_edge.argtypes = [c_bool, POINTER(Edge)]
exp.del_list.argtypes = [c_bool, POINTER(List)]

