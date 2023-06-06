/*
This main.c file is built using ADS (AURIX Development Studio) and can be inserted into any example project for building. The call to Ifx_FftF32_radix2 is located in the iLLD's sysse/math path. The input parameter for this function is a complex array defined as follows:

/* INPUT Data used by the example */
csint16 X1Q15_fft1024_[fftLength_fft1024] = {
/* Real Imaginary */
{0xD2B7, 0x4453}, // -0.35379 + 0.53381i
{0xB812, 0x69E1} // -0.56195 + 0.82718i
};

Each integer value in the array ranges from -32768 to 32767, representing the range of -1 to 1. The real and imaginary parts are specified for each value, and the result is processed in the same manner.
*/

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "ADC_Filtering.h"
#include "Bsp.h"

/*FFT test */
#include "IfxCbs_reg.h"

#include "SysSe/Math/Ifx_FftF32.h"

#define SAMPLES 1024
IfxCpu_Perf g_perfCounts;



IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;
extern csint16 X1Q15_fft1024_[1024];
void core0_main(void)
{

    cfloat32 X___[SAMPLES];  // input signal
    cfloat32 R1___[SAMPLES];  // output signal
    cfloat32 R2___[SAMPLES];  // output signal
    /*FFT test */
    int i;

    /*FFT test */
    IfxCpu_enableInterrupts();
    
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    
    /*FFT test */
    // create a test input signal (sinusoidal)
    for (i = 0; i < SAMPLES; i++) {

        X___[i].real=(float32)X1Q15_fft1024_[i].real/32768;
        X___[i].imag=(float32)X1Q15_fft1024_[i].imag/32768;

    }

    // generate twiddle factor table
    cfloat32 TF[SAMPLES/2];
    Ifx_FftF32_generateTwiddleFactor(TF, SAMPLES);

    // perform FFT using radix-2 algorithm

    Ifx_FftF32_radix2(R1___, X___, SAMPLES);

    for (i = 0; i < SAMPLES; i++) {
        R1___[i].real=(float32)R1___[i].real/1024*32768;
        R1___[i].imag=(float32)R1___[i].imag/1024*32768;

    }

}
