from base import layer

r = layer.Relu()
print(layer.get_opcode(r))
print(r)
c = layer.toClip(r)
print(layer.get_opcode(c))
c = layer.toClip(c)
print(layer.get_opcode(c))
