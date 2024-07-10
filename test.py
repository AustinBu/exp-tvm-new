from base import layer

r = layer.Relu()
print(layer.get_opcode(r))
c = layer.toClip(r)
print(layer.get_opcode(c))