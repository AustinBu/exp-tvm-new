from load_json_to_graph import *
from load_graph_to_json import *
import json

def print_edges(edges):
    for edge in edges:
        e = model.get_edge(edge)
        print("Edge" + str(edge.id) + ": ", end=" ")
        print(str(e[0]) + str(e[1]) + ",", str(e[2]) + str(e[3]))

def create_dummy_node(opcode):
    abc = Attrs * len([])
    attr_arr = abc(*([]))

    list_attr = model.new_list(attr_arr, len([]), 4)
    n = model.new_node_from_all(opcode, list_attr)[0]
    nodes.append(n)
    return n

f = open('./onnx/json/non-zero.json')
data = json.load(f)

model, nodes, edges = load_json_to_model(data)
initializer_list = []
for node in nodes:
    if node.opcode == 0:
        initializer_list.append(node)
graph = model.new_graph(edges)[0]
pattern = [8, 7]
pattern_edges = model.pattern_find(graph, pattern)[0]
for i in range(pattern_edges.size):
    edge = pattern_edges.getData()[i]
    id = edge.id

    index = model.get_edge_by_id(id)[0]
    
    val1 = edges[index-1].start[0].getData()[1].ints[0]
    val2 = edges[index+1].start[0].getData()[1].ints[0]
    res = [edge.getStartId(), edge.getEndId()]

    for _ in range(2):
        res = model.delete_edge(model.edges[index-1])
        del edges[index-1]

    if val1 == val2:
        if not 0 in res:
            model.set_end(res[0], res[1].end)
        for _ in range(2):
            if len(edges) != 0:
                model.delete_edge(model.edges[index-1])
                del edges[index-1]
    else:
        val = 0
        dummy_node = 0
        val = val1 - val2
        if edge.getStartOp() == 8 and edge.getEndOp() == 7:
            val = 0-val
        if val > 0:
            dummy_node = create_dummy_node(7)
        else:
            dummy_node = create_dummy_node(8)
            val = 0-val

        for node in initializer_list:
            if node.getData()[1].ints[0] == val:
                e = model.new_edge(node, dummy_node)
                edges.insert(index-1, e[0])

        if not 0 in res:
            model.set_end(res[0], nodes[-1])
            model.set_start(res[1], nodes[-1])

        if len(edges) != 0:
            id = edges[index].id
            model.delete_edge(model.get_edge_by_id(id)[1])
            del edges[index]

    print()
    print("Graph: ")
    print_edges(edges)

print(model_to_json("add_sub_graph", edges, data))

# breakpoint()

# model.delete_edge(model.edges[3])
# del edges[3]