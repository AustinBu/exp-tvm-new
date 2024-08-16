# exp-tvm

Custom IR based on Apache TVM

Loads an onnx model into a Graph object, making it easier to run optimizations

include/ -> header files
src/ -> cpp files
onnx -> onnx/json models for testing
python/ -> core functionality in python

By Elliu Huang and Austin Bu

# Overview
1. Load an onnx model to json 
2. Load the json into graph
3. Run optimizations on graph
4. Convert graph back into json

# base.py
Contains all the python structs, and library
Defines functions externed from cpp

# graph.py
Wrapper class to use the library with
Auto deletes all objects at the end of program

# Important to Note
The data type enum is not actually synced with onnx
A lot of this is highly specific to certain outputs, and not generalized
Understanding the logic is more important than actual execution