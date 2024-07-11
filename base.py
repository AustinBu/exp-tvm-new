from ctypes import *

exp = cdll.LoadLibrary('./exp.so')

class Object(Structure):
    _fields_ = [("opcode", c_int)]

exp.new_object.argtypes = [c_int]
exp.new_object.restype = POINTER(Object)
exp.get_opcode.argtypes = [POINTER(Object)]
exp.get_opcode.restype = c_int
