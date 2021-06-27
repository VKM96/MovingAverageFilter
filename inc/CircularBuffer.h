/**
 * @file CircularBuffer.h
 * @author vishal K
 * @brief Interface Circular buffer implementation
 * @date 2020-12-20
 * 
 * 
 */
#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stddef.h>
#include <stdint.h>
#include "Common.h"

/**
 * @brief Maximum circular buffer size maintained here 
 * 
 */
const size_t MAX_CIRCULAR_BUFFER_SIZE = 16 ;

/**
 * @brief Circular buffer structure
 * 
 */
typedef struct sCircBuffer_t
{
    int16_t head;
    int16_t tail;
    size_t numElems;
    size_t circBufSize;
    int16_t buf[MAX_CIRCULAR_BUFFER_SIZE] ; ///> The buffer size is statically allocated, adjust according to needs

}sCircBuffer_t;

/**
 * @brief Circular buffer structure handle
 * 
 */
typedef struct sCircBuffer_t* pHandleCircBuffer;

eStatusMAF_t circBuffer_Init(pHandleCircBuffer const pMe, const size_t size);
eStatusMAF_t circBuffer_Enqueue(pHandleCircBuffer const pMe, const int16_t data);
eStatusMAF_t circBuffer_Dequeue(pHandleCircBuffer const pMe, int16_t* pData);
eStatusMAF_t circBuffer_Peek(pHandleCircBuffer const pMe, int16_t* pData);
eStatusMAF_t circBuffer_GetOldestData(pHandleCircBuffer const pMe, int16_t* pData);
size_t circBuffer_GetNumElements(pHandleCircBuffer const pMe);


#endif