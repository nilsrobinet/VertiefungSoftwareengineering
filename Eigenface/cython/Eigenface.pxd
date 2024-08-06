cdef extern from "EigenfaceMain.h" namespace "Eigenface":
    cdef const int dimX
    cdef const int dimY
    cdef const int batchSize
    cdef const int numberOfEigenfaces
    
    cdef cppclass Eigenface:
        Eigenface()
        void getAverageFace(float[dimX*dimY*batchSize], float[dimX*dimY])
        void getDeviationFromAverageFace(float[dimX*dimY*batchSize])
