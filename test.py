from base import exp

r = exp.Relu()
print(exp.get_opcode(r))
print(r)
c = exp.toClip(r)
print(exp.get_opcode(c))
c = exp.toClip(c)
print(exp.get_opcode(c))
