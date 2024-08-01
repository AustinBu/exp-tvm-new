from python.base import *
from python.graph import Model
import numpy as np

m = Model()

r = m.relu()
print(m)

c = m.new_node(6)[0]
print(c.opcode)

e = m.new_edge(r, c)[0]
print(m.get_edge(e))
nodeList = []

for i in range(1):
    a = m.new_attrs(b"strides", 1, [1, 2, 3, 4, 6])[0]
    print(a.name, id(a))
    b = m.new_attrs(b"padding", 1, [1, 2, 3, 4, 5])[0]
    print(b.name, id(b))
    print(a.ints[4], b.ints[4])

    ab = []
    ab.append(a)
    ab.append(b)
    abtype = Attrs * len(ab)
    attr_arr = abtype(*ab)

    attr_list = m.new_list(attr_arr, len(ab), 4)
    n = m.new_node_from_all(5, attr_list)
    nodeList.append(n[0])

for i in range(1):
    c = m.new_attrs(b"dil", 1, None, 1)
    c_list = m.new_list(c, 1, 4)
    n1 = m.new_node_from_all(5, c_list)
    nodeList.append(n1[0])

for i in range(2):
    print(nodeList[0].getData()[i].name)
    if nodeList[0].getData()[i].ints_size != 0:
        print(nodeList[0].getData()[i].ints[4])
    else:
        print(nodeList[0].getData()[i].i)

for i in range(1):
    print(nodeList[1].getData()[i].name)
    if nodeList[1].getData()[i].ints_size != 0:
        print(nodeList[1].getData()[i].ints[0])
    else:
        print(nodeList[1].getData()[i].i)

# x = n.contents.attrs.contents
# print(x.name.decode('utf-8'))