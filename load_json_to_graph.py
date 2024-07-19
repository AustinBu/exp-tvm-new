import json 
from python.base import *
from python.layer import Layer
from python.opmap import *
import atexit

l = Layer()
atexit.register(l.cleanup)
f = open('./onnx/json/simple_cnn.json')
data = json.load(f)

def typeToInt(type):
    if type == "INTS" or type == "INT":
        return 1

node_data = data['graph']['node']
node_map = {node_data[i]['name'] : {'input': node_data[i]['input'], 'output': node_data[i]['output']} for i in range(len(node_data))}
initializer_names = set([data['graph']['initializer'][i]['name'] for i in range(len(data['graph']['initializer']))])
input_names = [data['graph']['input'][i]['name'] for i in range(len(data['graph']['input']))]
output_names = [data['graph']['output'][i]['name'] for i in range(len(data['graph']['output']))]
in_out_names = set(input_names + output_names)
print("initializer_names", initializer_names)
print("in_out_names", in_out_names)

nodeList = []
for node in node_data:
    attr_list = []
    attrs = node.get("attribute", None)
    if attrs != None:
        for attr in attrs:
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

model_edges = []
for i in range(len(nodeList)-1):
    model_edges.append(l.new_edge(nodeList[i], nodeList[i+1]))

for edge in model_edges:
    print(l.get_edge(edge))