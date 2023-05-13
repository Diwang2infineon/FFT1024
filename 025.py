#The purpose of the 025.py code is to generate shuffle numbers for Q15 1024 FFT, specifically for use in pass 5.

fft_indices = list(range(1024))



pass_val = 2
n = 4
temp_array = [[0 for i in range(1024//n)] for j in range(n)]

# populate temp_array with fft_indices values
for i in range(1024):
    index = (i // 4)
    temp_array[i % 4][index] = fft_indices[i]




# combine values from temp_array into fft_indices
for i in range(n):
    for j in range(1024//n):
        fft_indices[i*(1024//n) + j] = temp_array[i][j]
print(fft_indices)


pass_val = 3
n = 4**(pass_val - 1)
n=16
temp_array = [[0 for i in range(1024//n)] for j in range(n)]

# populate temp_array with fft_indices values
for j in range(n//4):
    for i in range(4096//n):
        
        group = (i % 4)
        index=(i//4)
        temp_array[ group+j*4][  index    ] = fft_indices[i+j*256]


print(temp_array)

# combine values from temp_array into fft_indices
for i in range(n):
    for j in range((1024//n)):
        fft_indices[i*(1024//n) + j] = temp_array[i][j]
print(fft_indices)


pass_val = 4
n = 4**(pass_val - 1)
n=64
temp_array = [[0 for i in range(1024//n)] for j in range(n)]

# populate temp_array with fft_indices values
for j in range(n//4):
    for i in range(4096//n):
        
        group = (i % 4)
        index=(i//4)
        temp_array[ group+j*4][  index    ] = fft_indices[i+j*(4096//n)]


print(temp_array)

# combine values from temp_array into fft_indices
for i in range(n):
    for j in range((1024//n)):
        fft_indices[i*(1024//n) + j] = temp_array[i][j]
print(fft_indices)


pass_val = 5
n = 4**(pass_val - 1)
n=256
temp_array = [[0 for i in range(1024//n)] for j in range(n)]

# populate temp_array with fft_indices values
for j in range(n//4):
    for i in range(4096//n):
        
        group = (i % 4)
        index=(i//4)
        temp_array[ group+j*4][  index    ] = fft_indices[i+j*(4096//n)]


print(temp_array)

# combine values from temp_array into fft_indices
for i in range(n):
    for j in range((1024//n)):
        fft_indices[i*(1024//n) + j] = temp_array[i][j]


for i in range(256):
    v=fft_indices[i*4]
    if(v>=128):
        v = v-256
    print(v,",0,0,0,")





