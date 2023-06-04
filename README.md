# FFT1024
python and .m code
https://octave-online.net/




# Python code
##  022.py:

The Python script `022.py` generates a complex array consisting of 1024 points that represent a sine waveform.

##  023.py:

The script `023.py` converts the complex array from a hexadecimal format to a float format that ranges from -1 to 1. The resulting complex array is also of size 1024.

##  024.py:

Finally, the script `024.py` converts the output from `023.py` to a format that can be imported into a MATLAB program. The resulting output is saved to a text file named `024output.txt`.

## 025.py:
The purpose of the `025.py` code is to generate shuffle numbers for Q15 1024 FFT, specifically for use in pass 5.


## 026.py
This Python code converts signed bytes to int16 and outputs the real and imaginary parts of the twiddle values.

## 027.py
Python Code: Converting Signed Bytes to Int16 and Extracting Twiddle Values
This Python code converts signed bytes to int16 and outputs the real and imaginary parts of the twiddle values.
The purpose of the "027.py" script is to convert all signed bytes into 16-bit signed integers. By dividing the obtained values by 32768, we can convert them into real and imaginary values ranging from -1 to 1. The script also utilizes the W factor for an FFT length of 1024 to determine the value of k for each twiddle.
For the "etwiddle" case, there are 256 * 3 twiddles, resulting in a total of 768 twiddles. Similarly, for the "ptwiddle" case, there are 64 * 3 twiddles, resulting in a total of 192 twiddles. Overall, there are 960 twiddles in total, each associated with a specific value of k.
- 256 * 3 = 768 for etwiddle
- 64 * 3 = 192 for ptwiddle
- 320 * 3 = 960 for all the twiddles

## 032.py
An alternative method for generating a reordering sequence involves utilizing bit reversal. You can find an example implementation in the .py file.


# C code

## SoftwareFFT_main.c

This `SoftwareFFT_main.c` file is built using ADS (AURIX Development Studio) and can be inserted into any example project for building. The call to `Ifx_FftF32_radix2` is located in the iLLD's `sysse/math` path. The input parameter for this function is a complex array defined as follows:

```c
/* INPUT Data used by the example */
csint16 X1Q15_fft1024_[fftLength_fft1024] = {
    /* Real  Imaginary */
    {0xD2B7, 0x4453},   // -0.35379 + 0.53381i
    {0xB812, 0x69E1}    // -0.56195 + 0.82718i
};
```
Each integer value in the array ranges from -32768 to 32767, representing the range of -1 to 1. The real and imaginary parts are specified for each value, and the result is processed in the same manner.



## 001.c 
This .c file is used to calculate the radix-4 DIF, which is verified by a 16-point FFT. The results obtained are compared with the Q15 16-point radix-4 DIF assembly code.

## 002.c Fast Fourier Transform (FFT) Implementation

This C code implements a software Fast Fourier Transform (FFT) algorithm to perform a 16-point FFT using the standard radix-2 decimation-in-time (DIT) approach. Additionally, it supports a 1024-point FFT.

### Overview

The FFT algorithm is widely used to convert time-domain signals into their frequency-domain representations. The radix-2 DIT algorithm recursively divides the input signal into smaller blocks and applies the FFT operation to each block.

The code includes the necessary functions and data structures to perform the FFT. It utilizes the `cfloat32` structure to represent complex numbers, which consist of real and imaginary parts. The code also defines lookup tables for twiddle factors and bit-reversed indices.

### Main Function

The `main` function serves as the entry point for the code. It initializes the input array and arranges it in bit-reversed order. Then, it calls the `Ifx_FftF32_radix2DecimationInTime` function to perform the FFT on the input array.

### Supporting Functions

The following supporting functions are used within the FFT algorithm:

- `Ifx_FftF32_lookUpReversedBits`: This function retrieves the bit-reversed index for a given value.
- `Ifx_FftF32_lookUpTwiddleFactor`: It returns the twiddle factor based on the FFT size and index.
- `IFX_Cf32_mul`: This function performs complex multiplication of two `cfloat32` numbers.
- `IFX_Cf32_add`: It adds two `cfloat32` numbers.
- `IFX_Cf32_sub`: This function subtracts two `cfloat32` numbers.

### FFT Result

The resulting FFT output is printed to the console using the `printf` function.

### Notes

Please note that the code assumes the existence of external data structures and constants, such as `Ifx_g_FftF32_twiddleTable` and `Ifx_g_FftF32_bitReverseTable`, which are not included in this code snippet.




# MATLAB code

## 03.m
This `.m` file is used to perform a 16-point Q15 FFT using the provided assembly code. The output is scaled by dividing each value by 16 and then multiplying by 32768 to make it comparable with the Q15 format used in the 16-point FFT assembly code.

## 04.m
In this MATLAB code, a 256 Hz sine waveform is generated with 1024 points. The sample rate is set to 1024 Hz, and the FFT result is computed up to 1024 Hz. By analyzing the output FFT result, you can observe a peak at 256 Hz, corresponding to the frequency of the generated waveform.

Since the Nyquist frequency is half of the sample rate (512 Hz in this case), any frequencies exceeding the Nyquist frequency can be ignored in the output FFT result.
