import numpy as np

N = 16384
twiddles = np.zeros(N, dtype=np.complex128)

with open('022.txt', 'w') as f:
    for k in range(N):
        twiddle = np.exp(-1j * 2 * np.pi * k / N)
        twiddles[k] = twiddle
        f.write(f"k = {k}, real = {twiddle.real:.20f}, imag = {twiddle.imag:.20f}\n")
