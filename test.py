from python.base import exp
from python.layer import Layer
import numpy as np
from ctypes import *

l = Layer()
r = l.relu()
print(l)

c = l.new_node(6)
print(c.contents.opcode)

e = l.new_edge(r, c)
print(l.get_edge(e))

array = np.array([1, 2, 3, 4, 5], dtype=np.int32)
a = exp.new_attrs(1, 1, array.ctypes.data_as(POINTER(c_int)), len(array), array.ctypes.data_as(POINTER(c_int)), len(array))
n = exp.new_node_from_all(5, a)
x = n.contents.attrs.contents
arr = np.ctypeslib.as_array(x.inshape, shape=(5,))

breakpoint()