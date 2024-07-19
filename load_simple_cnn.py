import json
from dataclasses import dataclass, field
from typing import List, Dict, Any
from python.opmap import opcodemap
from python.graph import Graph


@dataclass
class Attribute:
    name: str
    type: str
    ints: List[int] = field(default_factory=list)
    i: int = None

@dataclass
class Node:
    input: List[str]
    output: List[str]
    name: str
    opType: int
    attribute: List[Attribute] = field(default_factory=list)

def parse_attributes(attributes: List[Dict[str, Any]]) -> List[Attribute]:
    parsed_attributes = []
    for attr in attributes:
        type_ = attr.get('type', '')
        ints = [int(x) for x in attr.get('ints', [])]
        i = int(attr.get('i', 0)) if 'i' in attr else None
        parsed_attributes.append(Attribute(type_, ints, i))
    return parsed_attributes

def parse_json(json_data: List[Dict[str, Any]]) -> List[Node]:
    nodes = []
    for node_data in json_data:
        input_ = node_data.get('input', [])
        output = node_data.get('output', [])
        name = node_data.get('name', '')
        opType = opcodemap[node_data.get('opType', '')]
        attributes_data = node_data.get('attribute', [])
        attributes = parse_attributes(attributes_data)
        nodes.append(Node(input_, output, name, opType, attributes))
    return nodes

def main():
    # Read JSON data from file
    with open('onnx/json/simple_cnn.json', 'r') as f:
        json_data = json.load(f)
        node_data = json_data['graph']['node']

    node_map = {node_data[i]['name'] : {'input': node_data[i]['input'], 'output': node_data[i]['output']} for i in range(len(node_data))}
    print(node_map)
    
    initializer_names = set([json_data['graph']['initializer'][i]['name'] for i in range(len(json_data['graph']['initializer']))])
    input_names = [json_data['graph']['input'][i]['name'] for i in range(len(json_data['graph']['input']))]
    output_names = [json_data['graph']['output'][i]['name'] for i in range(len(json_data['graph']['output']))]
    in_out_names = set(input_names + output_names)
    print("initializer_names", initializer_names)
    print("in_out_names", in_out_names)
    
    # Parse JSON data into list of nodes
    nodes = parse_json(node_data)
    
    # Print parsed nodes for verification
    for node in nodes:
        print(node.name)
    
    print("----------")
    model = Graph()
    model_nodes = {}
    model_edges = []
    for n in nodes:
        model_nodes[n.name] = model.new_node(n.opType)
        for i in n.input:
            if i not in initializer_names or i not in in_out_names:
                # find the node name with output = input of the curr node
                for k in node_map:
                    if i in node_map[k]['output']:
                        model_edges.append(model.new_edge(model_nodes[k], model_nodes[n.name]))
        
    print(model)

if __name__ == "__main__":
    main()