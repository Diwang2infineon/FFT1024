    // This .c file is used to calculate radix 4 decimation in frequency (DIF) FFT algorithm
    // It is verified by performing a 16-point FFT and comparing the results with the Q15 16-point radix 4 DIF assembly code
    // The input and output are in complex format

    // 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI2 6.283185307179586476925286766559005768394338798750211641949889184615632812572417997256069650684234

void FFTR4(double *X, double *Y, int N, int M) {
    int N1, N2;
    int I1, I2, I3;
    double CO1, CO2, CO3, SI1, SI2, SI3;
    double A, B, C, E;
    double R1, R2, R3, R4;
    double S1, S2, S3, S4;
    // N = 1 << (M+M);
    N2 = N;
    I2 = 0; I3 = 0;
    for (int K=0; K<M; ++K) {
        N1 = N2;
        N2 = N2 / 4;
        E = PI2 / (double)N1;
        A = 0.0;
        for (int J=0; J < N2; ++J) {
            A = J*E;
            B = A + A;
            C = A + B;
            // Should be pre-calculated for optimization
            CO1 = cos(A);
            CO2 = cos(B);
            CO3 = cos(C);
            SI1 = sin(A);
            SI2 = sin(B);
            SI3 = sin(C);
            for (int I = J; I<N; I+=N1) {
                I1 = I + N2;
                I2 = I1 + N2;
                I3 = I2 + N2;
                R1 = X[I] + X[I2];
                R3 = X[I] - X[I2];
                S1 = Y[I] + Y[I2];
                S3 = Y[I] - Y[I2];
                R2 = X[I1] + X[I3];
                R4 = X[I1] - X[I3];
                S2 = Y[I1] + Y[I3];
                S4 = Y[I1] - Y[I3];
                X[I] = R1 + R2;
                R2 = R1 - R2;
                R1 = R3 - S4;
                R3 = R3 + S4;
                Y[I] = S1 + S2;
                S2 = S1 - S2;
                S1 = S3 + R4;
                S3 = S3 - R4;
                X[I1] = CO1*R3 + SI1*S3;
                Y[I1] = CO1*S3 - SI1*R3;
                X[I2] = CO2*R2 + SI2*S2;
                Y[I2] = CO2*S2 - SI2*R2;
                X[I3] = CO3*R1 + SI3*S1;
                Y[I3] = CO3*S1 - SI3*R1;
            }
        }
    }
    // Radix-4 bit-reverse
    double T;
    int J = 0;
    N2 = N>>2;
    for (int I=0; I < N-1; I++) {
        if (I < J) {
            T = X[I];
            X[I] = X[J];
            X[J] = T;
            T = Y[I];
            Y[I] = Y[J];
            Y[J] = T;
        }
        N1 = N2;
        while (J >= 3*N1) {
            J -= 3*N1;
            N1 >>= 2;
        }
        J += N1;
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
