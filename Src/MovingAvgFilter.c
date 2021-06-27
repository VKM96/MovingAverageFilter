/**
 * @file MovingAvgFilter.c
 * @author vishal K
 * @brief Moving Average filter implementation
 * @date 2020-12-20
 * 
 * 
 */

#include "MovingAvgFilter.h"
#include <string.h>
#include <assert.h>

/**
 * @brief Filter initialization function
 * 
 * @param pMe : Moving avg filter handle
 * @param sampleSize : Sample size for the moving average filter
 * @return eStatusMAF_t : e_SUCCESS on success
 * @note Sample size needs to be less than circular buffer max size @ref circBuffer_Init
 */
eStatusMAF_t filter_Init(pHandleFilter const pMe, const size_t sampleSize)
{
    eStatusMAF_t status = e_FAIL;
    assert(NULL != pMe);

    pMe->avg = 0;
    pMe->sum = 0;
    status = circBuffer_Init( &(pMe->m_filterCircularBuffer),sampleSize);

    return status;
}

/**
 * @brief function that current moving average
 * 
 * @param pMe : Moving avg filter handle 
 * @return int16_t : Moving average 
 */
int16_t filter_GetAvg(pHandleFilter const pMe)
{
    assert(NULL != pMe);
    return pMe->avg;
}

/**
 * @brief function for adding data into filter 
 * 
 * @param pMe : Moving avg filter handle 
 * @param data : data to be added into the filter
 * @return eStatusMAF_t : e_SUCCESS on success
 */
eStatusMAF_t filter_DataIn(pHandleFilter const pMe, const int16_t data)
{
    assert(NULL != pMe);
    eStatusMAF_t status = e_SUCCESS;

    pHandleCircBuffer filterBufferHandle = (&(pMe->m_filterCircularBuffer));

    int16_t oldestSample = 0;
    circBuffer_GetOldestData(filterBufferHandle,&oldestSample);
    status = circBuffer_Enqueue(filterBufferHandle,data);

    if(e_OVERWRITE == status)
    {
        pMe->sum -= oldestSample;
    }
    pMe->sum += data ;
    pMe->avg = (int16_t)(((float)pMe->sum/circBuffer_GetNumElements(filterBufferHandle))*100) ; 

    return status;
}


