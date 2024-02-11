# This code snippet imports the NumPy library for numerical operations.
# It initializes a variable N to 16384 and creates an array 'twiddles' of complex numbers with N elements.
# The code then iterates over the range of N, computing complex exponential values for each index 'k' and storing them in the 'twiddles' array.
# Finally, it writes the index 'k' and the corresponding real and imaginary parts of the computed complex number into a text file named '022.txt'.

import numpy as np

N = 16384
twiddles = np.zeros(N, dtype=np.complex128)

with open('022.txt', 'w') as f:
    for k in range(N):
        twiddle = np.exp(-1j * 2 * np.pi * k / N)
        twiddles[k] = twiddle
        f.write(f"k = {k}, real = {twiddle.real:.20f}, imag = {twiddle.imag:.20f}\n")
