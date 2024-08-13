# For add/sub only right now

import json
from python.graph import Model

def model_to_json(name,  edgeList, original_json):
    m = Model()
    data = {
        'graph': {
            'initializer': [],
            'node': [],
            'name': name,
            'input': [],
            'output': []
        }
    }

    prev_sub = 1
    prev_add = 1
    i = 0
    while i < len(edgeList):
        print(m.get_edge(edgeList[i]))
        node_data = {
            'name': "",
            'opType': "",
            'input': [],
            'output': [],
        }

        out_name = ""
        if edgeList[i].getEndOp() == 8:
            node_data['name'] = "/sub" + str(prev_sub) + "/Sub"
            node_data['opType'] = "Sub"
            out_name = "output_sub" + str(prev_sub)
        elif edgeList[i].getEndOp() == 7:
            node_data['name'] = "/add" + str(prev_add) + "/Add"
            node_data['opType'] = "Add"
            out_name = "output_add" + str(prev_add)
        node_data['output'].append(out_name)

        op = edgeList[i].getStartOp()
        if op != 0:
            in_name = ""
            if op == 8:
                in_name = "output_sub" + str(prev_sub)
                prev_sub += 1
            elif op == 7:
                in_name = "output_add" + str(prev_add)
                prev_add += 1
            node_data['input'].append(in_name)
            i += 1
        if edgeList[i].getStartOp() == 0:
            node_data['input'].append("one") # hardcode
            if i == 0:
                node_data['input'].append("input")

        data['graph']['node'].append(node_data)
        i += 1
        print(node_data)
        print()
    data['graph']['input'] = original_json['graph']['input']
    data['graph']['output'] = original_json['graph']['output']
    data['graph']['initializer'] = original_json['graph']['initializer']

    return json.dumps(data, indent=4)
