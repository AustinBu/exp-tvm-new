import json 

f = open('./onnx/json/simple_cnn.json')

data = json.load(f)

nameList = []
for node in data['graph']['node']:
    nameList.append(node['name'])
print(nameList)