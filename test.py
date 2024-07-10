from base import layer

r = layer.Relu()
print(layer.get_opcode(r))
c = layer.toClip(r)
c = layer.toClip(c)
print(layer.get_opcode(c))