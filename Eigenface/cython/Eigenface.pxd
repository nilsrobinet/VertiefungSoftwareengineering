cdef extern from "EigenfaceMain.h" namespace "Eigenface":

    cdef cppclass Eigenface:
        Eigenface()
        void getAverageFace(float[256*256*8], float[256*256])
