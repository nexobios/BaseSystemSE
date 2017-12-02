#include "fir_filter.h"

void fir_filter(float *fInputData, float *fFIRCoeff, float *fOutputData, uint32_t u32InputDataSize, uint32_t u32KSize)
{
    uint32_t u32Counter = 0;
    uint32_t u32KCounter = 0;

    /* Cleaning the Array */
    memset(fOutputData, (float)0, sizeof(float)*u32InputDataSize);

    for(u32Counter = 0; u32Counter < u32InputDataSize; u32Counter++)
    {
        for(u32KCounter = 0; u32KCounter < u32KSize; u32KCounter++)
        {
            if(u32KCounter <= u32Counter)
            {
                fOutputData[u32Counter] += (float)(fFIRCoeff[u32KCounter]*fInputData[u32Counter - u32KCounter]);
            }
        }
    }
    /* Return is not necessary */
}