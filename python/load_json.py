import json 

f = open('../onnx/json/simple_cnn.json')

data = json.load(f)

for node in data['graph']['node']:
    print(node['opType'])