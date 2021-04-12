import ctypes
import numpy
import glob

# find the shared library, the path depends on the platform and Python version
libfile = glob.glob('build/*/Addbook*.so')[0]

# 1. open the shared library
mylib = ctypes.CDLL(libfile)

class Books(object):
    def __init__(self):
        self.obj = mylib.b_new()

    def myFunc(self):
        mylib.B_func(self.obj)

f = Books()
f.add_book()
