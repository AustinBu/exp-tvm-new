from ctypes import *

exp = cdll.LoadLibrary('./exp.so')

class Object(Structure):
    _fields_ = [("opcode", c_int)]

class Layer:
    def __init__(self):
        self.layers = []

    def __str__(self):
        s = "Layers["
        for l in self.layers:
            if l.contents.opcode == 5:
                s += "Relu()"
        s += "]"
        return s

    def relu(self):
        self.layers.append(exp.new_object_from_opcode(5))
        return self.layers[-1]

exp.new_object_from_opcode.argtypes = [c_int]
exp.new_object_from_opcode.restype = POINTER(Object)
exp.new_object_from_object.argtypes = [POINTER(Object)]

exp.get_opcode.argtypes = [POINTER(Object)]
exp.get_opcode.restype = c_int
