from python.base import exp
from python.layer import Layer
import numpy as np

l = Layer()
r = l.relu()
print(l)

c = l.new_node(6)
print(c.opcode)

e = l.new_edge(r, c)
print(l.get_edge(e))

array = np.array([1, 2, 3, 4, 5], dtype=np.int32)
a = l.new_attrs(1, 1, array, array)
n = l.new_node_all(5, a)
x = n.contents.attrs.contents
print(np.ctypeslib.as_array(x.inshape, shape=(5,)))

