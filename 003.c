
/* This C code generates 17 decimal digital twiddle numbers of 16384.
It is intended for comparison with equivalent Python and MATLAB code. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 16384
#define PI 3.14159265358979323846

int main(int argc, char *argv[]) {
	FILE *fp;
	double twiddle_real, twiddle_imag;
	int i;
	
	fp = fopen("022.txt", "w");
	if (fp == NULL) {
		printf("Error opening file!");
		return 0;
	}
	
	for (i = 0; i < N; i++) {
		twiddle_real = cos(-2 * PI * i / N);
		twiddle_imag = sin(-2 * PI * i / N);
		fprintf(fp, "%10.20f,", twiddle_real);
		fprintf(fp, "%10.20f\n", twiddle_imag);
	}
	
	fclose(fp);
	
	return 0;
}
