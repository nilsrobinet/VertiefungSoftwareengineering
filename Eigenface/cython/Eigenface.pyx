
cdef extern from "EigenfaceMain.h" namespace "Eigenface":

    cdef class Eigenface:
        Eigenface() except +
