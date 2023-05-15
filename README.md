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
