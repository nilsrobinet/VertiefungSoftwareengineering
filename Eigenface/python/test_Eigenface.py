import os,sys
import numpy as np
# add bin to path to be able to import Eigenface module
sys.path.append(os.path.join(os.path.dirname(os.path.realpath(__file__)), '..','..','bin'))
from Eigenface import PyEigenface

def printArr(arr):
    for cnt,i in enumerate(arr):
        print(f'{i}, ',end='')
        if cnt % 32 == 0:
            print()

def test_averageFaceSimple():
    allZeros = np.zeros( (256,256,8), dtype=np.float32 )
    pyEf = PyEigenface()
    resBuffer = pyEf.getAverageFace(allZeros)
    expected = 0.0
    assert(np.sum(resBuffer) == expected);
    assert(not np.any(resBuffer))
    
    allOnes = np.ones( (256,256,8), dtype=np.float32 )
    resBuffer = pyEf.getAverageFace(allOnes)
    expected = 256.0*256.0
    assert(np.sum(resBuffer) == expected)
    assert(np.all(resBuffer))
    
    
def test_getDeviationFromAverageFace():
    np.random.seed(0)
    randomInput_1 = np.random.rand(255,255,8).astype(np.float32)
    randomInput_2 = np.copy(randomInput_1)
    
    numpy_out =  np.array([inp.T - np.average(randomInput_1,axis=2) for inp in randomInput_2.T]).T
    
    pyEf = PyEigenface()
    
    result = pyEf.getDeviationFromAverageFace(randomInput_1);
    breakpoint()