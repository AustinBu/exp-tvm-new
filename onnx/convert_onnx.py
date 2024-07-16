import onnx2json
import json

# Convert the ONNX model to JSON
onnx_model_path = "simple_relu.onnx"
# onnx_model_path = 'mnist-1.onnx'

onnx_json = onnx2json.convert(onnx_model_path)

# Save the JSON to a file
json_output_path = 'simple_relu.json'
# json_output_path = 'mnist-1.json'

with open(json_output_path, 'w') as json_file:
    json.dump(onnx_json, json_file, indent=4)

print(f"ONNX model converted to JSON and saved to {json_output_path}")