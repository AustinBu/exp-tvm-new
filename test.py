from python.base import *
from python.layer import Layer
import numpy as np
import atexit

l = Layer()
atexit.register(l.cleanup)

r = l.relu()
print(l)

c = l.new_node(6)
print(c.contents.opcode)

e = l.new_edge(r, c)
print(l.get_edge(e))

a = l.new_attrs(b"strides", 1, [1, 2, 3, 4, 6])[0]
print(a.name, id(a))
print(a.ints[4])
b = l.new_attrs(b"padding", 1, [1, 2, 3, 4, 5])[0]
print(b.name, id(b))
print(a.ints[4])
print(b.ints[4])
c = l.new_attrs(b"dil", 1, None, 1)[0]

ab = []
ab.append(a)
ab.append(b)
ab.append(c)
abc = Attrs * len(ab)
attr_arr = abc(*ab)

# exp.print_attr_list(attr_arr, len(ab))
n = l.new_node_from_all(5, attr_arr, len(ab))
print(n.contents.attrs[0].name)
print(n.contents.attrs[1].name)

# x = n.contents.attrs.contents
# print(x.name.decode('utf-8'))