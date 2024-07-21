from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import numpy

ext_modules = [
    Extension(
        "Eigenface",
        sources=["Eigenface.pyx"],
        include_dirs=[numpy.get_include(), '../include'],
        libraries=["Eigenface"],
        #library_dirs=['/path/to/Eigenface/bin']
    )
]

setup(
    name="Eigenface",
    ext_modules=cythonize(ext_modules),
)