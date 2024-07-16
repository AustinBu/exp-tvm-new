import urllib.request

# Download a simple ONNX model
url = 'https://github.com/onnx/models/blob/main/validated/vision/classification/mnist/model/mnist-1.onnx'
onnx_model_path = 'mnist-1.onnx'
urllib.request.urlretrieve(url, onnx_model_path)
