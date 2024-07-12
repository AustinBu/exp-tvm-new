from base import exp
from base import Layer

l = Layer()
r = l.relu()
print(l)

c = exp.new_node_from_opcode(6)
print(c.contents.opcode)

e = exp.new_edge(r, c)
print(e.contents.start.contents.opcode)
print(e.contents.end.contents.opcode)
