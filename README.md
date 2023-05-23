# FFT1024
python and .m code
https://octave-online.net/



# Script Descriptions
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

# C code

## 001.c 
This .c file is used to calculate the radix-4 DIF, which is verified by a 16-point FFT. The results obtained are compared with the Q15 16-point radix-4 DIF assembly code.

# MATLAB code

## 03.m
This `.m` file is used to perform a 16-point Q15 FFT using the provided assembly code. The output is scaled by dividing each value by 16 and then multiplying by 32768 to make it comparable with the Q15 format used in the 16-point FFT assembly code.

## 04.m
In this MATLAB code, a 256 Hz sine waveform is generated with 1024 points. The sample rate is set to 1024 Hz, and the FFT result is computed up to 1024 Hz. By analyzing the output FFT result, you can observe a peak at 256 Hz, corresponding to the frequency of the generated waveform.

Since the Nyquist frequency is half of the sample rate (512 Hz in this case), any frequencies exceeding the Nyquist frequency can be ignored in the output FFT result.
