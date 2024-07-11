from ctypes import *

exp = cdll.LoadLibrary('./exp.so')

exp.Relu.restype = POINTER(c_void_p)
# exp.get_opcode.argtypes = [POINTER(c_void_p)]
exp.get_opcode.restype = c_int
exp.toClip.restype = POINTER(c_void_p)
