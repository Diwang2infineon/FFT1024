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

/** \brief Define custom types */
typedef unsigned int uint32;
typedef unsigned int boolean_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8;
typedef unsigned char uint8_t;
typedef float float32;
typedef signed char sint8;

/** \brief Define structures for QSPI */
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

/** \brief Structure for extended configuration of QSPI */
typedef struct
{
    uint32 U;
    struct
    {
        uint32 Q     : 6;
        uint32 A     : 6;
        uint32 C     : 6;
        uint32 B     : 6;
        uint32 CPH   : 1;
        uint32 CPOL  : 1;
        uint32 PAREN : 1;
        uint32 reserved : 5;
    } B;
} Ifx_QSPI_ECON;

/** \brief Structure for channel configuration of SPI */
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

/** \brief Boolean enumeration */
typedef enum
{
    FALSE = 0,
    TRUE = 1
} boolean;

/** \brief Macro for absolute value */
#define __absf(X) ((X) < 0.0 ? -(X) : (X))

/** \brief Macro for less than or equal to comparison for floats */
#define __leqf(X, Y) (!(X > Y))

/** \brief Macro for greater than or equal to comparison for floats */
#define __geqf(X, Y) (!(X < Y))

/** \brief Macro for not equal to comparison for floats */
#define __neqf(X,Y) (((X) > (Y)) || ((X) < (Y)))

/**
 * \brief Function to calculate extended configuration value for QSPI
 *
 * \param qspi Pointer to QSPI structure
 * \param cs Chip select
 * \param chConfig Pointer to channel configuration
 * \return Calculated extended configuration value
 */
uint32 IfxQspi_calculateExtendedConfigurationValue(Ifx_QSPI *qspi, const uint8 cs, const SpiIf_ChConfig *chConfig)
{
    Ifx_QSPI_ECON econ;
    econ.U = 0;

    const int     maxB   = 3;
    float32       tQspi  = 1.0 / 100000000; // IfxQspi_getTimeQuantaFrequency(qspi);
    float32       fBaud  = 20000000; // (chConfig->baudrate);
    int           abcMin = (2);
    int           abcMax = (4 + 0 + 4);
    int           q, bestQ = 1, abc, bestAbc = abcMax, halfBaud = 0;
    sint8         diffB  = 0;
    float32       error, bestError;
    float32       tTmp, tBaudTmp;
    boolean       done = FALSE;

    if (fBaud == 0.0)
    {
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

        if (__leqf(error, bestError))
        {
            if (__neqf(error, bestError) || (((uint32)bestAbc & (uint32)0x1) == 0))
            {
                bestError = error;
                bestAbc   = abc;
                bestQ     = q;
            }

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

    if ((bestQ <= abcMax) && (((uint32)bestAbc & (uint32)0x1) != 0) && (((uint32)bestQ & (uint32)0x1) == 0))
    {
        q       = bestQ;
        bestQ   = bestAbc;
        bestAbc = q;
    }

    halfBaud     = bestAbc / 2;
    diffB        = halfBaud - maxB;

    econ.B.Q     = bestQ - 1;
    econ.B.A     = halfBaud + (bestAbc % 2) - 1;
    econ.B.C     = (diffB > 0) ? diffB : 0;
    econ.B.B     = (diffB > 0) ? maxB : halfBaud;
    econ.B.PAREN = chConfig->mode.parityCheck;

    return econ.U;
}

/** \brief Main function */
int main()
{
    Ifx_QSPI qspi;  // Assuming QSPI is initialized
    SpiIf_ChConfig chConfig;
    chConfig.baudrate = 20000000;  // Set baud rate to 20 MHz
    chConfig.mode.parityCheck = 0;
    chConfig.mode.clockPolarity = 0;
    chConfig.mode.shiftClock = 1;

    uint32_t econValue = IfxQspi_calculateExtendedConfigurationValue(&qspi, 0, &chConfig);

    printf("Ifx_QSPI_ECON value: 0x%08X\n", econValue);

    return 0;
}
