cdef extern from "EigenfaceMain.h" namespace "Eigenface":

    cdef cppclass Eigenface:
        Eigenface()
        void getAverageFace(float[256*256*8], float[256*256])
        void getDeviationFromAverageFace(float[dimX*dimY*batch])

    C dimX "Eigenface::Eigenface::dimX"
    C dimY "Eigenface::Eigenface::dimY"
    C batch "Eigenface::Eigenface::batch"