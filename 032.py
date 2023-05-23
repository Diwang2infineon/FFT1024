'''
An alternative method for generating a reordering sequence involves 
utilizing bit reversal. You can find an example implementation in 
the following .py file, as well as refer to another function called
Ifx_FftF32_reverseBits() in the software FFT source code:

[Link to .py file]

The Ifx_FftF32_reverseBits() function provides an additional way
to achieve bit reversal for reordering sequences.

'''

def bit_reversal_1024():
    num_points = 1024
    num_bits = 10
    reversed_indices = [0] * num_points

    for index in range(num_points):
        reversed_index = 0
        temp_index = index

        for bit in range(num_bits):
            reversed_index <<= 1
            reversed_index |= temp_index & 1
            temp_index >>= 1

        reversed_indices[index] = reversed_index

    return reversed_indices




print(bit_reversal_1024())
