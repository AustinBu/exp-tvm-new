import onnx
import onnx2json
import json
from onnxruntime.datasets import get_example

# Step 1: Get a simple ONNX model
model_path = get_example('sigmoid.onnx')

# Step 2: Load the ONNX model
onnx_model = onnx.load(model_path)

# Save the ONNX model to a specific path
onnx_model_output_path = 'sigmoid.onnx'
onnx.save(onnx_model, onnx_model_output_path)

# Step 3: Convert the ONNX model to JSON
onnx_json = onnx2json.convert(model_path)

# Step 4: Save the JSON to a file
json_output_path = 'sigmoid.json'
with open(json_output_path, 'w') as json_file:
    json.dump(onnx_json, json_file, indent=4)

print(f"ONNX model saved to {onnx_model_output_path}")
print(f"ONNX model converted to JSON and saved to {json_output_path}")
