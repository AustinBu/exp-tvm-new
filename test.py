from python.base import *
from python.graph import Graph
import numpy as np

l = Graph()

r = l.relu()
print(l)

c = l.new_node(6)
print(c.contents.opcode)

e = l.new_edge(r, c)
print(l.get_edge(e))
nodeList = []

for i in range(1):
    a = l.new_attrs(b"strides", 1, [1, 2, 3, 4, 6])[0]
    print(a.name, id(a))
    b = l.new_attrs(b"padding", 1, [1, 2, 3, 4, 5])[0]
    print(b.name, id(b))
    print(a.ints[4], b.ints[4])

    ab = []
    ab.append(a)
    ab.append(b)
    abtype = Attrs * len(ab)
    attr_arr = abtype(*ab)

    attr_list = l.new_list(attr_arr, len(ab), 0)
    n = l.new_node_from_all(5, attr_list)
    nodeList.append(n[0])

for i in range(1):
    c = l.new_attrs(b"dil", 1, None, 1)
    c_list = l.new_list(c, 1, 0)
    n1 = l.new_node_from_all(5, c_list)
    nodeList.append(n1[0])

for i in range(2):
    print(nodeList[0].getData()[i].name)
    if nodeList[0].getData()[i].ints_size != 0:
        print(nodeList[0].getData()[i].ints[1])
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