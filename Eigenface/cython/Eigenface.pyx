cimport Eigenface as cef
from cpython cimport array
from libc.stdlib cimport malloc, free
import array
#cimport numpy as npc
import numpy as np
cimport numpy as np

cdef class PyEigenface:
    cdef Eigenface c_eigenface
    
    def __init__(self):
        self.c_eigenface = cef.Eigenface()
        
    def getAverageFace(self, np.ndarray[np.float32_t, ndim=3] faces):
        cdef float* faces_ptr = <float*> faces.data
        cdef np.ndarray[np.float32_t, ndim=2] avg_face = np.empty((256, 256), dtype=np.float32)
        cdef float* avg_face_ptr = <float*> avg_face.data
        self.c_eigenface.getAverageFace(faces_ptr, avg_face_ptr)
        return avg_face

    def getDeviationFromAverageFace(self, np.ndarray[np.float32_t, ndim=3] faces):
        cdef float* faces_ptr = <float*> faces.data
        self.c_eigenface.getDeviationFromAverageFace(faces_ptr)