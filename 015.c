/******************************************************************************
 * \file QSPI_Configuration.c
 *
 * \brief Configuration calculation for QSPI
 *
 * This file provides a function to calculate the extended configuration value
 * for QSPI based on specified parameters. It defines structures and functions
 * required for the calculation.
 *
 * \version 1.0
 *
 ******************************************************************************/


#include <stdio.h>

// Define custom types
typedef unsigned int uint32;
typedef unsigned char uint8;
typedef float float32;

typedef signed char sint8;



typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef signed char sint8_t;
typedef float float32_t;
typedef unsigned char boolean_t;

typedef struct
{
    volatile unsigned int GLOBALCON;
    volatile unsigned int STATUS;
    volatile unsigned int FLAGSTATUS;
    volatile unsigned int FLAGCLEAR;
    volatile unsigned int TRIGSRC;
    volatile unsigned int TRIGEN;
    volatile unsigned int TRIGDIS;
    volatile unsigned int TRIGCNT;
    volatile unsigned int FMR;
    volatile unsigned int RXEXIT;
    volatile unsigned int RXEXITCNT;
    volatile unsigned int RXEXITINT;
    volatile unsigned int RXEXITINTEN;
    volatile unsigned int RXEXITINTDIS;
    volatile unsigned int RXEXITINTCNT;
    volatile unsigned int RXEXITINTSR;
    volatile unsigned int RXEXITINTCLR;
    volatile unsigned int RXEXITINTSET;
    volatile unsigned int RXEXITINTTGL;
    volatile unsigned int RXEXITINTMSK;
    volatile unsigned int RXEXITINTMASK;
} Ifx_QSPI;

typedef struct
{
    uint32_t U;
    struct
    {
        uint32_t Q     : 6;
        uint32_t A     : 6;
        uint32_t C     : 6;
        uint32_t B     : 6;
        uint32_t CPH   : 1;
        uint32_t CPOL  : 1;
        uint32_t PAREN : 1;
        uint32_t reserved : 5;
    } B;
} Ifx_QSPI_ECON;

typedef struct
{
    uint32_t baudrate;
    struct
    {
        boolean_t parityCheck;
        uint8_t   clockPolarity;
        uint8_t   shiftClock;
    } mode;
} SpiIf_ChConfig;

typedef enum
{
    FALSE = 0,
    TRUE = 1
} boolean;










#define __absf(X) ((X) < 0.0 ? -(X) : (X))

#define __leqf(X, Y) (!(X > Y)) /**< X <= Y */
#define __geqf(X, Y) (!(X < Y)) /**< X >= Y */


#define __neqf(X,Y)                     ( ((X) > (Y)) ||  ((X) < (Y)) )     /**< X != Y */


uint32 IfxQspi_calculateExtendedConfigurationValue(Ifx_QSPI *qspi, const uint8 cs, const SpiIf_ChConfig *chConfig)
{
    //IFX_UNUSED_PARAMETER(cs);

    Ifx_QSPI_ECON econ;
    econ.U = 0;

    const int     maxB   = 3;
    float32       tQspi  = 1.0 / 100000000;// IfxQspi_getTimeQuantaFrequency(qspi);
    float32       fBaud  =20000000;// (chConfig->baudrate);
    int           abcMin = (2);
    int           abcMax = (4 + 0 + 4);
    int           q, bestQ = 1, abc, bestAbc = abcMax, halfBaud = 0;
    sint8         diffB  = 0;
    float32       error, bestError;
    float32       tTmp, tBaudTmp;
    boolean       done = FALSE;

    if (fBaud == 0.0)
    {
        //IFX_ASSERT(IFX_VERBOSE_LEVEL_WARNING, FALSE);   /* chosen baud rate is 0 */
        fBaud = 1.0;
    }

    float32 tBaud = 1.0 / fBaud;

    bestError = 1e6;

    for (abc = abcMax; abc >= abcMin; abc--)
    {
        tTmp = tQspi * abc;
        q    = (int)((tBaud / tTmp) + 0.5);

        if (q > 64)
        {
            q = 64;
        }

        else if ((q * abc) < 4)
        {
            q = 2;
        }

        else if (q < 1)
        {
            q = 1;
        }

        tBaudTmp = tTmp * q;
        error    = __absf(tBaudTmp - tBaud);

        if (__leqf(error, bestError)) /* we have a equal/better error case */
        {
            /* process this case only if lesser error / or if ABC is even */
            if (__neqf(error, bestError) || (((uint32)bestAbc & (uint32)0x1) == 0))
            {
                bestError = error;
                bestAbc   = abc;
                bestQ     = q;
            }

            /* break out if ABC is even and error = 0 */
            if (((uint32)bestAbc & (uint32)0x1) == 0)
            {
                done = (__neqf(error, 0.0)) ? FALSE : TRUE;

                if (done != FALSE)
                {
                    break;
                }
            }
        }
    }

    /* Exchange Q and ABC, if ABC is odd and Q is even.
     * This is because: A+1+B+C is ideally even for
     * achieving 50% duty cycle of the clock.
     */
    if ((bestQ <= abcMax)
        && (((uint32)bestAbc & (uint32)0x1) != 0)
        && (((uint32)bestQ & (uint32)0x1) == 0))
    {
        q       = bestQ;
        bestQ   = bestAbc;
        bestAbc = q;
    }

    /* NOTE: In assigning values to A,B,C:
     *  the "sampling point" (which is A+B) has to be as far as possible
     *  from the "shifting point" (end of A+B+C).
     * The duty cycle is calculated as the ratio of A : B+C
     * Therefore, to keep 50% duty cycle: A = B+C
     * Thus, we cannot influence the value of A, once A+B+C is found out
     * (A+1 is always (A+B+C)/2).
     * However, in between B and C - we should try to maximize B (and minimize C).
     * The goal will be to do this - keep max value of B always and keep only any remaining value for C .
     */
    halfBaud     = bestAbc / 2;
    diffB        = halfBaud - maxB;

    econ.B.Q     = bestQ - 1;
    econ.B.A     = halfBaud + (bestAbc % 2) - 1;  /* A + 1 = Half of Baud count */
    econ.B.C     = (diffB > 0) ? diffB : 0;
    econ.B.B     = (diffB > 0) ? maxB : halfBaud;

    //econ.B.CPH   = (chConfig->mode.shiftClock == SpiIf_ShiftClock_shiftTransmitDataOnLeadingEdge) ? 1 : 0;
    //econ.B.CPOL  = (chConfig->mode.clockPolarity == SpiIf_ClockPolarity_idleLow) ? 0 : 1;
    econ.B.PAREN = chConfig->mode.parityCheck;

    return econ.U;
}
















int main()
{
    Ifx_QSPI qspi;  // 假设已经初始化
    SpiIf_ChConfig chConfig;
    chConfig.baudrate = 20000000;  // 设置波特率为 20 MHz
    chConfig.mode.parityCheck = 0;
    chConfig.mode.clockPolarity = 0;
    chConfig.mode.shiftClock = 1;

    uint32_t econValue = IfxQspi_calculateExtendedConfigurationValue(&qspi, 0, &chConfig);

    printf("Ifx_QSPI_ECON value: 0x%08X\n", econValue);

    return 0;
}
