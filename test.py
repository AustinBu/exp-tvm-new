from python.base import *
from python.layer import Layer
import numpy as np

l = Layer()
r = l.relu()
print(l)

c = l.new_node(6)
print(c.contents.opcode)

e = l.new_edge(r, c)
print(l.get_edge(e))

# array = np.array([1, 2, 3, 4, 5], dtype=np.int32)
# a = l.new_attrs(1, 1, array, array)
a = l.new_attrs(b"strides", 1, np.array([1, 2, 3, 4, 5], dtype=np.int32))[0]
print(a.name, id(a))
b = l.new_attrs(b"padding", 1, np.array([1, 2, 3, 4, 5], dtype=np.int32))[0]
print(b.name, id(b))

# c = l.new_attrs("wow", 1, np.array([1, 2, 3, 4, 5], dtype=np.int32))[0]

# print()
# a1 = Attrs((b"dilation"), 1, np.array([1, 2, 3, 4, 5], dtype=np.int32).ctypes.data_as(POINTER(c_int)), 5)
# b1 = Attrs((b"group"), 1, np.array([1, 2, 3, 4, 5], dtype=np.int32).ctypes.data_as(POINTER(c_int)), 5)

ab = []
ab.append(a)
ab.append(b)
abc = Attrs * len(ab)
attr_arr = abc(*ab)

# exp.print_attr_list(attr_arr, len(ab))
n = l.new_node_all(5, attr_arr, len(ab))
print(n.contents.attrs[0].name)
print(n.contents.attrs[1].name)
breakpoint()
# x = n.contents.attrs.contents
# print(x.name.decode('utf-8'))