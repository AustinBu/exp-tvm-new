from python.base import Attrs
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
a = l.new_attrs("strides", 1, np.array([1, 2, 3, 4, 5], dtype=np.int32))
b = l.new_attrs("padding", 1, np.array([1, 2, 3, 4, 5], dtype=np.int32))
ab = [a, b]

attrs_seq = Attrs * len(ab)
attrs = attrs_seq(*ab)

n = l.new_node_all(5, a)
x = n.contents.attrs.contents
print(x.name.decode('utf-8'))
