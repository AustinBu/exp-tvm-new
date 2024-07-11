import ctypes

librelu = ctypes.CDLL('./librelu.so')  

librelu.ReLU_new.argtypes = [ctypes.c_int]
librelu.ReLU_new.restype = ctypes.c_void_p

librelu.ReLU_set_input.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
librelu.ReLU_set_input.restype = None

librelu.ReLU_activate.argtypes = [ctypes.c_void_p]
librelu.ReLU_activate.restype = None

librelu.ReLU_print.argtypes = [ctypes.c_void_p]
librelu.ReLU_print.restype = None

class ReLU:
    def __init__(self, size):
        self.obj = librelu.ReLU_new(size)

    def set_input(self, values):
        c_values = (ctypes.c_int * len(values))(*values)
        librelu.ReLU_set_input(self.obj, c_values)

    def activate(self):
        librelu.ReLU_activate(self.obj)

    def print(self):
        librelu.ReLU_print(self.obj)


if __name__ == "__main__":
    values = [5, -3, 8, -1, 0, 7]
    size = len(values)

    relu = ReLU(size)
    relu.print()

    print(relu)