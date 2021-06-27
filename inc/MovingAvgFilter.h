/**
 * @file MovingAvgFilter.h
 * @author vishal K
 * @brief Interface for Average filter implementation
 * @date 2020-12-20
 * 
 * 
 */

#ifndef MOVINGAVGFILTER_H
#define MOVINGAVGFILTER_H

#include <stdint.h>
#include <stddef.h>
#include "Common.h"
#include "CircularBuffer.h"

/**
 * @brief Structure that holds moving average filter parameters
 * @note @see sCircBuffer_t
 */
typedef struct sAvgFilter_t
{
    int16_t sum;    
    int16_t avg;
    sCircBuffer_t m_filterCircularBuffer; /**< Circular buffer instance,*/

}sAvgFilter_t;

/**
 * @brief Handle typdef for moving average filter
 * 
 */
typedef struct sAvgFilter_t* pHandleFilter;


eStatusMAF_t filter_Init(pHandleFilter const pMe, const size_t sampleSize);
eStatusMAF_t filter_DataIn(pHandleFilter const pMe, const int16_t data);
int16_t filter_GetAvg(pHandleFilter const pMe);


#endif