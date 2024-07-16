import onnx
import onnx.helper as helper


# Create a simple graph with a single ReLU layer
input_tensor = helper.make_tensor_value_info('input', onnx.TensorProto.FLOAT, [1, 3])
output_tensor = helper.make_tensor_value_info('output', onnx.TensorProto.FLOAT, [1, 3])

node_def = helper.make_node(
    'Relu',       # The operation name (Op name)
    ['input'],    # The inputs
    ['output'],   # The outputs
)

# Create the graph (GraphProto)
graph_def = helper.make_graph(
    [node_def],
    'simple-relu-model',
    [input_tensor],
    [output_tensor],
)

# Create the model (ModelProto)
model_def = helper.make_model(graph_def, producer_name='onnx-examples')

# Save the model
onnx_model_path = 'simple_relu.onnx'
onnx.save(model_def, onnx_model_path)
