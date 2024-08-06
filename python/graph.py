from python.base import *
from python.maps import *
from ctypes import *
import atexit

map = opmap
debug = True

class Model:
    def __init__(self):
        self.nodes = []
        self.edges = []
        self.attrs = []
        self.lists = []
        self.graph = []
        atexit.register(self.cleanup)

    def __str__(self):
        s = "Layers["
        for l in self.nodes:
            # breakpoint()
            if l.contents.opcode == 5:
                s += "Relu(), "
            elif l.contents.opcode == 1:
                s += "Conv(), "
        s += "]"
        return s

    def relu(self):
        self.nodes.append(exp.new_node_from_opcode(5))
        return self.nodes[-1]
    
    def new_node(self, opcode):
        self.nodes.append(exp.new_node_from_opcode(opcode))
        return self.nodes[-1]
    
    def new_node_from_all(self, opcode, attrs_list):
        self.nodes.append(exp.new_node_from_all(opcode, attrs_list))
        return self.nodes[-1]

    def new_edge(self, start, end):
        self.edges.append(exp.new_edge(start, end))
        return self.edges[-1]
    
    def get_edge(self, edge):
        return map[edge.getStartOp()], edge.start[0].id, map[edge.getEndOp()], edge.end[0].id
    
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

    def new_list(self, arr, size, type):
        arr = cast(arr, c_void_p)
        l = exp.new_list(arr, size, type)
        self.lists.append(l)
        return l
    
    def typeToInt(self, strType):
        single = False
        intType = -1
        if strType == "INTS" or strType == "INT":
            intType = 1

        if strType ==  "INT":
            single = True
        return single, intType
    
    def new_graph(self, edgeList):
        datatype = Edge * len(edgeList)
        edge_arr = datatype(*edgeList)
        edge_list = self.new_list(edge_arr, len(self.edges), 6)
        graph = exp.new_graph(edge_list)
        self.graph.append(graph)
        return graph
    
    def pattern_find(self, graph, pattern):
        list = exp.pattern_find(
            graph, 
            self.handleInts(pattern),
            len(pattern))
        self.lists.append(list)
        return list

    def del_attrs(self, attrs):
        exp.del_attrs(debug, attrs)

    def del_node(self, node):
        exp.del_node(debug, node)

    def del_edge(self, edge):
        exp.del_edge(debug, edge)

    def del_list(self, list):
        exp.del_list(debug, list)

    def del_graph(self, graph):
        exp.del_graph(debug, graph)

    def cleanup(self):
        for n in self.nodes:
            self.del_node(n)
        for e in self.edges:
            self.del_edge(e)
        for a in self.attrs:
            self.del_attrs(a)
        for l in self.lists:
            self.del_list(l)
        for g in self.graph:
            self.del_graph(g)

