import ctypes
import numpy as np
from numpy.ctypeslib import ndpointer

# Cargar la biblioteca compartida
lib = ctypes.CDLL('lib/SEC.so')
# Definir el tipo de argumento y el tipo de retorno
lib.separation_procedure.argtypes = [np.ctypeslib.ndpointer(dtype=np.float64, ndim=2, flags='C_CONTIGUOUS'), ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
lib.separation_procedure.restype = ctypes.POINTER(ctypes.c_int)

def SEC(xval, epsilon, n):
    matrix = np.zeros((n, n), dtype=np.float64)
    for i in range(n):
        for j in range(n):
            if i != j and xval[i, j] > epsilon:
                matrix[i, j] = xval[i,j]

    # Llamar a la función desde Python
    result_size = ctypes.c_int()
    result_ptr = lib.separation_procedure(matrix, n, ctypes.byref(result_size))
    
    if result_size.value == -1:
        return []
    #print("El resultado de la suma es:", resultado)
    # Convertir el resultado de un arreglo de una dimensión a NumPy
    return np.ctypeslib.as_array(result_ptr, shape=(result_size.value,))
