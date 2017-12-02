#include "fir_filter.h"

/* Filter properties:
   - Order: 10 
   - Type:  PASSBAND
   - fc0:   0.2*nqst freq 
   - fc1:   0.6*nqst freq 
*/
const float fCoeffArray[MAX_FILTER_SIZE] = {
  0.005751808383355,
  -0.077001789640512,
  -0.198038134660382,
  0.125026660533693,
  0.474150515430546,
  0.125026660533693,
  -0.198038134660382,
  -0.077001789640512,
  0.005751808383355,
  0
};

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