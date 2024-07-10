from ctypes import *

layer = cdll.LoadLibrary('./layer.so')

layer.Relu.restype = POINTER(c_void_p)
layer.get_opcode.argtypes = [POINTER(c_void_p)]
layer.get_opcode.restype = c_int
layer.toClip.restype = POINTER(c_void_p)
