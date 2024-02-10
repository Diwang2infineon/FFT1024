/* 
   Name: Radix-4 Fast Fourier Transform (FFT)
   Author: [Author's Name]
   Description: This program implements the Radix-4 Fast Fourier Transform (FFT) algorithm for complex inputs. It calculates the FFT of an input sequence of size N, where N must be a power of 4. The function FFTR4 performs the FFT calculation.

   Parameters:
   - inputReal: Array containing the real part of the input sequence.
   - inputImag: Array containing the imaginary part of the input sequence.
   - size: Size of the input sequence (must be a power of 4).
   - log2Size: Log base 2 of the size of the input sequence.

   The function first divides the input sequence into smaller sub-sequences and then performs the FFT on each sub-sequence iteratively. It utilizes the Cooley-Tukey algorithm for decimation in time. The FFT is calculated in place, meaning the input arrays are modified to contain the FFT result.

   Example Usage:
   - Define an array to hold the real part of the input sequence (X1Q15_fft16_real) and another array for the imaginary part (X1Q15_fft16_imag).
   - Call the FFTR4 function with the real and imaginary parts of the input sequence, the size of the sequence (N), and the logarithm base 2 of the size (M).
   - The FFT result will be stored in the input arrays.
   - Print the real and imaginary parts of the FFT result.

   Note: This program assumes that the input sequence size is a power of 4.

   Reference:
   - Cooley, James W., and John W. Tukey. "An algorithm for the machine calculation of complex Fourier series." Mathematics of Computation 19.90 (1965): 297-301.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI2 6.283185307179586476925286766559005768394338798750211641949889184615632812572417997256069650684234

void FFTR4(double *inputReal, double *inputImag, int size, int log2Size) {
    int size1, size2;
    int index1, index2, index3;
    double cos1, cos2, cos3, sin1, sin2, sin3;
    double angleA, angleB, angleC, angleStep;
    double tempR1, tempR2, tempR3, tempR4;
    double tempI1, tempI2, tempI3, tempI4;
    
    size2 = size;
    index2 = 0; index3 = 0;
    
    for (int stage = 0; stage < log2Size; ++stage) {
        size1 = size2;
        size2 = size2 / 4;
        angleStep =  PI2 / (double)size1;
        angleA = 0.0;
        
        for (int j = 0; j < size2; ++j) {
            angleA = j * angleStep;
            angleB = angleA + angleA;
            angleC = angleA + angleB;
            
            cos1 = cos(angleA);
            cos2 = cos(angleB);
            cos3 = cos(angleC);
            sin1 = sin(angleA);
            sin2 = sin(angleB);
            sin3 = sin(angleC);
            printf("cos1=%lf, sin1=%lf \n",cos1,-sin1);
            printf("cos2=%lf, sin2=%lf \n",cos2,-sin2);
            printf("cos3=%lf, sin3=%lf \n",cos3,-sin3);
            
            for (int i = j; i < size; i += size1) {
                index1 = i + size2;
                index2 = index1 + size2;
                index3 = index2 + size2;
                
                tempR1 = inputReal[i] + inputReal[index2];
                tempR3 = inputReal[i] - inputReal[index2];
                tempI1 = inputImag[i] + inputImag[index2];
                tempI3 = inputImag[i] - inputImag[index2];
                
                tempR2 = inputReal[index1] + inputReal[index3];
                tempR4 = inputReal[index1] - inputReal[index3];
                tempI2 = inputImag[index1] + inputImag[index3];
                tempI4 = inputImag[index1] - inputImag[index3];
                //printf("i=%d, j=%d ",i,j);
                inputReal[i] = tempR1 + tempR2;
                tempR2 = tempR1 - tempR2;
                tempR1 = tempR3 - tempI4;
                tempR3 = tempR3 + tempI4;
                
                inputImag[i] = tempI1 + tempI2;
                tempI2 = tempI1 - tempI2;
                tempI1 = tempI3 + tempR4;
                tempI3 = tempI3 - tempR4;
                
                inputReal[index1] = cos1 * tempR3 + sin1 * tempI3;
                inputImag[index1] = cos1 * tempI3 - sin1 * tempR3;
                
                inputReal[index2] = cos2 * tempR2 + sin2 * tempI2;
                inputImag[index2] = cos2 * tempI2 - sin2 * tempR2;
                
                inputReal[index3] = cos3 * tempR1 + sin3 * tempI1;
                inputImag[index3] = cos3 * tempI1 - sin3 * tempR1;
            }
        }
    }
    
    // Radix-4 bit-reverse
    double temp;
    int j = 0;
    size2 = size >> 2;
    
    for    (int i = 0; i < size - 1; i++) {
        if (i < j) {
            temp = inputReal[i];
            inputReal[i] = inputReal[j];
            inputReal[j] = temp;
            
            temp = inputImag[i];
            inputImag[i] = inputImag[j];
            inputImag[j] = temp;
        }
        
        size1 = size2;
        
        while (j >= 3 * size1) {
            j -= 3 * size1;
            size1 >>= 2;
        }
        
        j += size1;
    }
}


int main() {
    // Example usage
    int N = 16; // Number of points
    int M = 2; // M = log4(N)
      double X1Q15_fft16_real[16] = {
        -0.35379, -0.56195, -0.55511, 0.32993, -0.35715, 0.07544, -0.63217, 0.35831,
        -0.22025, 0.65186, 0.64032, 0.16940, -0.00626, 0.72382, 0.58234, 0.26236
    };

    double X1Q15_fft16_imag[16] = {
        0.53381, 0.82718, 0.04089, 0.68829, -0.59216, 0.86865, -0.41385, -0.44846,
        0.68033, 0.42966, -0.65814, -0.88406, 0.71320, -0.54477, -0.36447, 0.29230
    };

    double X[16] = {0.0}; // Real part input
    double Y[16] = {0.0}; // Imaginary part input

    // Assign values to X and Y arrays
    for (int i = 0; i < 16; i++) {
        X[i] = X1Q15_fft16_real[i];
        Y[i] = X1Q15_fft16_imag[i];
    }

    FFTR4(X, Y, N, M);

    // Print the results
    for (int i = 0; i < N; i++) {
        printf("X[%d] = %lf, Y[%d] = %lf\n", i, X[i], i, Y[i]);
    }

    return 0;
}
