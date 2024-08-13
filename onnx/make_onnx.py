import onnx
import onnx.helper as helper
from onnx import TensorProto
import onnx2json
import json

# # Create a simple graph with a single ReLU layer
# input_tensor = helper.make_tensor_value_info('input', onnx.TensorProto.FLOAT, [1, 3])
# output_tensor = helper.make_tensor_value_info('output', onnx.TensorProto.FLOAT, [1, 3])

# node_def = helper.make_node(
#     'Relu',       # The operation name (Op name)
#     ['input'],    # The inputs
#     ['output'],   # The outputs
# )

# # Create the graph (GraphProto)
# graph_def = helper.make_graph(
#     [node_def],
#     'simple-relu-model',
#     [input_tensor],
#     [output_tensor],
# )

# # Create the model (ModelProto)
# model_def = helper.make_model(graph_def, producer_name='onnx-examples')

# # Save the model
# onnx_model_path = 'simple_relu.onnx'
# onnx.save(model_def, onnx_model_path)


# Create input tensor
input = helper.make_tensor_value_info('input', TensorProto.FLOAT, [1])

# Create output tensor
output_final = helper.make_tensor_value_info('output_final', TensorProto.FLOAT, [1])

# Create constant tensor for the value 1
one_tensor = helper.make_tensor("one", TensorProto.INT32, [1], [1])
two_tensor = helper.make_tensor("two", TensorProto.INT32, [1], [2])

nodeList = []

# Create Add and Sub nodes
nodeList.append(helper.make_node('Sub', ['input', 'one'], ['output_sub1'], "/sub1/Sub"))
for i in range(1, 1000):
    nodeList.append(helper.make_node(
        'Add', ['output_sub' + str(i), 'one'], ['output_add' + str(i)], "/add" + str(i) + "/Add"))
    nodeList.append(helper.make_node(
        'Sub', ['output_add' + str(i), 'one'], ['output_sub' + str(i + 1)], "/sub" + str(i + 1) + "/Sub"))
nodeList.append(helper.make_node('Add', ['output_sub1000', 'one'], ['output_final'], "/add1000/Add"))

# Create the graph
graph = helper.make_graph(
    nodeList,  # nodes
    'non-zero-graph',  # graph name
    [input],  # inputs
    [output_final],  # outputs
    [one_tensor, two_tensor]  # initializer (constant tensor)
)

# Create the model
model = helper.make_model(graph, producer_name='add_sub-model')

# Save the model to a file
onnx.save(model, 'onnx/model/add_sub.onnx')

# Convert the ONNX model to JSON
onnx_model_path = "onnx/model/add_sub.onnx"
# onnx_model_path = 'mnist-1.onnx'

onnx_json = onnx2json.convert(onnx_model_path)

# Save the JSON to a file
json_output_path = 'onnx/json/add_sub.json'
# json_output_path = 'mnist-1.json'

with open(json_output_path, 'w') as json_file:
    json.dump(onnx_json, json_file, indent=4)

print(f"ONNX model converted to JSON and saved to {json_output_path}")