import json 
from python.base import *
from python.layer import Layer
from python.opmap import opcodemap
import atexit

l = Layer()
atexit.register(l.cleanup)
f = open('./onnx/json/simple_cnn.json')
data = json.load(f)

def typeToInt(type):
    if type == "INTS" or type == "INT":
        return 1

nodeList = []
for node in data['graph']['node']:
    attr_list = []
    attrs = node.get("attribute", None)
    if attrs != None:
        for attr in attrs:
            print(attr)
            name = attr.get("name").encode("utf-8")
            ints = attr.get("ints")
            type = typeToInt(attr.get("type"))
            if ints != None:
                ints = list(map(int, ints))
                attr_list.append(l.new_attrs(name, type, ints)[0])
            else:
                i = int(attr.get("i"))
                attr_list.append(l.new_attrs(name, type, ints, i)[0])
    abc = Attrs * len(attr_list)
    attr_arr = abc(*attr_list)
    opcode = opcodemap.get(node.get("opType"))
    nodeList.append(l.new_node_from_all(opcode, attr_arr, len(attr_list))[0])

print(nodeList)
breakpoint()