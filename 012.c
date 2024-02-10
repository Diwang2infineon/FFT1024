/******************************************************************************
 * \file Ifx_LutSincosF32.c
 *
 * \brief Look-up Table (LUT) sine and cosine functions implementation
 *
 * This file contains the implementation of sine and cosine functions
 * using a pre-computed lookup table.
 *
 * \version iLLD_1_0_1_11_0
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 16384
#define PI 3.14159265358979323846

#define IFX_LUT_ANGLE_PI   (IFX_LUT_ANGLE_RESOLUTION / 2)
#define IFX_PI  3.14159265358979323846
#define IFX_LUT_ANGLE_RESOLUTION 4096
double Ifx_g_LutSincosF32_table[IFX_LUT_ANGLE_RESOLUTION/4];

void Ifx_LutSincosF32_init(void)
{
#if 1
    /* generate sin and cos table */
    int k;

    for (k = 0; k <= IFX_LUT_ANGLE_PI / 2; k++)
    {
        Ifx_g_LutSincosF32_table[k] = sinf((IFX_PI * 2 * k) / IFX_LUT_ANGLE_RESOLUTION);
    }
#endif
}

typedef int Ifx_Lut_FxpAngle;

float Ifx_LutSincosF32_sin(Ifx_Lut_FxpAngle fxpAngle)
{
    double result;
    fxpAngle = fxpAngle & (IFX_LUT_ANGLE_RESOLUTION - 1);

    if (fxpAngle < IFX_LUT_ANGLE_PI / 2)
    {
        result = Ifx_g_LutSincosF32_table[fxpAngle];
    }
    else if (fxpAngle < IFX_LUT_ANGLE_PI)
    {
        fxpAngle = IFX_LUT_ANGLE_PI - fxpAngle;
        result   = Ifx_g_LutSincosF32_table[fxpAngle];
    }
    else if (fxpAngle < IFX_LUT_ANGLE_PI / 2 * 3)
    {
        fxpAngle = fxpAngle - IFX_LUT_ANGLE_PI;
        result   = -Ifx_g_LutSincosF32_table[fxpAngle];
    }
    else
    {
        fxpAngle = IFX_LUT_ANGLE_RESOLUTION - fxpAngle;
        result   = -Ifx_g_LutSincosF32_table[fxpAngle];
    }

    return result;
}

int main(int argc, char *argv[])
{
    FILE *fp;
    double twiddle_real, twiddle_imag;
    int i;

    fp = fopen("022.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!");
        return 0;
    }

    for (i = 0; i < N; i++)
    {
        twiddle_real = cos(-2 * PI * i / N);
        twiddle_imag = sin(-2 * PI * i / N);
        // fprintf(fp, "%10.20f,", twiddle_real);
        // fprintf(fp, "%10.20f\n", twiddle_imag);
    }

    Ifx_LutSincosF32_init();

// Print the lookup table
printf("Lookup Table:\n");
for (i = 0; i < IFX_LUT_ANGLE_RESOLUTION/4; i++)
{
    printf("Table[%d] = %.20f\n", i, Ifx_g_LutSincosF32_table[i]);
}


    // Print the first few sine values from the lookup table
    for (i = 0; i < 10; i++)
    {
        float angle = (float)i * IFX_LUT_ANGLE_PI / IFX_LUT_ANGLE_RESOLUTION;
        float sinValue = Ifx_LutSincosF32_sin(angle);
        printf("sin(%.20f) = %.20f\n", angle, sinValue);
    }

    fclose(fp);

    return 0;
}
