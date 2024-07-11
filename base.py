from ctypes import *

exp = cdll.LoadLibrary('./exp.so')

class Object(Structure):
    _fields_ = [("opcode", c_int)]

exp.new_object_from_opcode.argtypes = [c_int]
exp.new_object_from_opcode.restype = POINTER(Object)
exp.new_object_from_object.argtypes = [POINTER(Object)]

exp.get_opcode.argtypes = [POINTER(Object)]
exp.get_opcode.restype = c_int
