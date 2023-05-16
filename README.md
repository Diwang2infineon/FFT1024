# FFT1024
python and .m code


# Script Descriptions

## Script 022.py:

The Python script `022.py` generates a complex array consisting of 1024 points that represent a sine waveform.

## Script 023.py:

The script `023.py` converts the complex array from a hexadecimal format to a float format that ranges from -1 to 1. The resulting complex array is also of size 1024.

## Script 024.py:

Finally, the script `024.py` converts the output from `023.py` to a format that can be imported into a MATLAB program. The resulting output is saved to a text file named `024output.txt`.

## The purpose of 025.py:
The purpose of the `025.py` code is to generate shuffle numbers for Q15 1024 FFT, specifically for use in pass 5.

## 03.m
This `.m` file is used to perform a 16-point Q15 FFT using the provided assembly code. The output is scaled by dividing each value by 16 and then multiplying by 32768 to make it comparable with the Q15 format used in the 16-point FFT assembly code.

## 001.c 
This .c file is used to calculate the radix-4 DIF, which is verified by a 16-point FFT. The results obtained are compared with the Q15 16-point radix-4 DIF assembly code.

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

