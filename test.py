from base import exp

r = exp.new_object_from_opcode(5)
print(r.contents.opcode)
exp.new_object_from_object(r)
print(r.contents.opcode)
