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

initial_data = data['graph']['initializer']
node_data = data['graph']['node']
node_map = {node_data[i]['name'] : {'input': node_data[i]['input'], 'output': node_data[i]['output']} for i in range(len(node_data))}
initializer_names = set([data['graph']['initializer'][i]['name'] for i in range(len(data['graph']['initializer']))])
input_names = [data['graph']['input'][i]['name'] for i in range(len(data['graph']['input']))]
output_names = [data['graph']['output'][i]['name'] for i in range(len(data['graph']['output']))]
in_out_names = set(input_names + output_names)

print()
print("initializer_names: ", initializer_names)
print("in_out_names: ", in_out_names)

nodeList = []
graphNodes = {}
edgeList = []

for i_node in initial_data:
    attr_list = []
    a = g.new_attrs(b'dims', i_node['dataType'], list(map(int, i_node['dims'])))[0]
    attr_list.append(a)
    abc = Attrs * len(attr_list)
    attr_arr = abc(*(attr_list))
    list_attr = g.new_list(attr_arr, len(attr_list), 0)
    nodeList.append(g.new_node_from_all(0, list_attr)[0])
    graphNodes[i_node['name']] = nodeList[-1]

for node in node_data:
    print()
    print("Parsing node: " + str(node.get("name")))

    attr_list = []
    attrs = node.get("attribute", None)
    if attrs != None:
        for attr in attrs:
            print("--> Parsing attr: " + str(attr))

            name = attr.get("name").encode("utf-8")
            ints = attr.get("ints")
            i = attr.get("i")

            single, type = g.typeToInt(attr.get("type"))
            if type == 1:
                if not single:
                    ints = list(map(int, ints))
                else:
                    i = int(i)
            a = g.new_attrs(name, type, ints, i)[0]
            print("Created new ATTRS: " + a.name.decode('utf-8'), id(a))
            attr_list.append(a)

    abc = Attrs * len(attr_list)
    attr_arr = abc(*(attr_list))
    opcode = opcodemap.get(node.get("opType"))

    list_attr = g.new_list(attr_arr, len(attr_list), 0)

    nodeList.append(g.new_node_from_all(opcode, list_attr)[0])
    print("Created new NODE: " 
          + str(get_op_from_code(nodeList[-1].opcode)) 
          + str(nodeList[-1].id), id(nodeList[-1]))

    graphNodes[node['name']] = nodeList[-1]
    for i in node['input']:
        if i in initializer_names:
            edgeList.append(g.new_edge(graphNodes[i], graphNodes[node['name']]))
        for k in node_map:
            if i in node_map[k]['output']:
                edgeList.append(g.new_edge(graphNodes[k], graphNodes[node['name']]))

    input(": ")

print()
for edge in edgeList:
    e = g.get_edge(edge)
    print("Edge" + str(edge.contents.id) + ": ", end=" ")
    print(str(e[0]) + str(e[1]) + ",", str(e[2]) + str(e[3]))

for node in nodeList:
    print()
    print(str(get_op_from_code(node.opcode)) + str(node.id))
    data = node.getData()
    if data != 0:
        for d in data:
            print("> " + str(d.name.decode('utf-8')), end=": ")
            if d.ints_size == 0:
                print(d.i)
            else:
                for i in range(d.ints_size):
                    print(d.ints[i], end=" ")
                print()