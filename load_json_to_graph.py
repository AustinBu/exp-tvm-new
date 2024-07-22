import json 
from python.base import *
from python.graph import Graph
from python.maps import *

g = Graph()
f = open('./onnx/json/simple_cnn.json')
data = json.load(f)

def printNode(n):
    print()
    print(n.id)
    print(n.opcode)
    print(n.attrs[0].size)
    print()

def typeToInt(strType):
    single = False
    intType = -1
    if strType == "INTS" or strType == "INT":
        intType = 1

    if strType ==  "INT":
        single = True
    return single, intType

node_data = data['graph']['node']
node_map = {node_data[i]['name'] : {'input': node_data[i]['input'], 'output': node_data[i]['output']} for i in range(len(node_data))}
initializer_names = set([data['graph']['initializer'][i]['name'] for i in range(len(data['graph']['initializer']))])
input_names = [data['graph']['input'][i]['name'] for i in range(len(data['graph']['input']))]
output_names = [data['graph']['output'][i]['name'] for i in range(len(data['graph']['output']))]
in_out_names = set(input_names + output_names)
print("initializer_names", initializer_names)
print("in_out_names", in_out_names)

nodeList = []
attr_list = []
list_refs = []
for node in node_data:
    start = len(attr_list)
    end = start

    attrs = node.get("attribute", None)
    if attrs != None:
        end = end + len(attrs)

        for attr in attrs:
            name = attr.get("name").encode("utf-8")
            ints = attr.get("ints")
            i = attr.get("i")

            single, type = typeToInt(attr.get("type"))
            if type == 1:
                if not single:
                    ints = list(map(int, ints))
                else:
                    i = int(i)
            a = g.new_attrs(name, type, ints, i)[0]
            attr_list.append(a)

    abc = Attrs * (end - start)
    attr_arr = abc(*(attr_list[start:end]))
    opcode = opcodemap.get(node.get("opType"))

    list_attr = g.new_list(attr_arr, (end - start))
    list_refs.append(list_attr)
    nodeList.append(g.new_node_from_all(opcode, list_attr)[0])

for node in nodeList:
    if node.attrs[0].size != 0:
        for i in range(node.attrs[0].size):
            data = node.attrs[0].data[i]
            print(data.name)
            for j in range(data.ints_size):
                print(data.ints[j], end = " ")

edgeList = []
for i in range(len(nodeList)-1):
    edgeList.append(g.new_edge(nodeList[i], nodeList[i+1]))

for edge in edgeList:
    print(g.get_edge(edge))

# for attrs in g.attrs:
#     attr = attrs[0]
#     print(attr.name)
#     print("ints = [", end = "")
#     for i in range(attr.ints_size):
#         print(attr.ints[i], end = "")
#         if i + 1 < attr.ints_size:
#             print(end=" ")
#     print("]")
#     if attr.i != 0:
#         print("i = %s" % attr.i)
#     print()

