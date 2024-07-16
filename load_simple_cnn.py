# import json

# f = open("onnx/json/simple_cnn.json")
# simple_cnn = json.load(f)

# for i in simple_cnn['graph']['node']:
#     print(i['opType'])
#     print()

import json
from dataclasses import dataclass, field
from typing import List, Dict, Any

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
    opType: str
    attribute: List[Attribute] = field(default_factory=list)

def parse_attributes(attributes: List[Dict[str, Any]]) -> List[Attribute]:
    parsed_attributes = []
    for attr in attributes:
        name = attr.get('name', '')
        type_ = attr.get('type', '')
        ints = [int(x) for x in attr.get('ints', [])]
        i = int(attr.get('i', 0)) if 'i' in attr else None
        parsed_attributes.append(Attribute(name, type_, ints, i))
    return parsed_attributes

def parse_json(json_data: List[Dict[str, Any]]) -> List[Node]:
    nodes = []
    for node_data in json_data:
        input_ = node_data.get('input', [])
        output = node_data.get('output', [])
        name = node_data.get('name', '')
        opType = node_data.get('opType', '')
        attributes_data = node_data.get('attribute', [])
        attributes = parse_attributes(attributes_data)
        nodes.append(Node(input_, output, name, opType, attributes))
    return nodes

def main():
    # Read JSON data from file
    with open('onnx/json/simple_cnn.json', 'r') as f:
        json_data = json.load(f)
        json_data = json_data['graph']['node']
    
    # Parse JSON data into list of nodes
    nodes = parse_json(json_data)
    
    # Print parsed nodes for verification
    for node in nodes:
        print(node)

if __name__ == "__main__":
    main()