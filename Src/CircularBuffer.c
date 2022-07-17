/**
 * @file CircularBuffer.c
 * @author vishal K
 * @brief Circular buffer implementation
 * @date 2020-12-20
 * 
 * 
 */

#include "CircularBuffer.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Utility function to check if buffer is empty 
 * 
 * @param pMe : Handle to circular buffer
 * @return true : if buffer empty 
 * @return false : if buffer is not empty
 */
static inline bool circBuffer_IsEmpty(pHandleCircBuffer const pMe)
{
    assert(NULL != pMe);
    return (0 == pMe->numElems);
}

/**
 * @brief Utility function to check if buffer is empty 
 * 
 * @param pMe : Handle to circular buffer
 * @return true : if buffer is full
 * @return false : : if buffer is not full
 */
static inline bool circBuffer_IsFull(pHandleCircBuffer const pMe)
{
    assert(NULL != pMe);
    return (pMe->numElems >= pMe->circBufSize );
}

/**
 * @brief Utility function to reset array used by circular buffer
 * 
 * @param pMe : Handle to circular buffer
 * @return eStatusMAF_t : e_SUCCESS on success
 */
static eStatusMAF_t static_ResetBuf(pHandleCircBuffer const pMe)
{
    assert(NULL != pMe);

    eStatusMAF_t status = e_SUCCESS;

    memset(pMe->buf, 0, MAX_CIRCULAR_BUFFER_SIZE * sizeof(pMe->buf[0]) );
    return status;
}

/**
 * @brief Function to initialize circular buffer
 * 
 * @param pMe : Handle to circular buffer
 * @param size : size to use for circular buffer
 * @return eStatus_t : e_SUCCESS on success
 * @note size should be smaller than max buffer capacity @see MAX_CIRCULAR_BUFFER_SIZE
 */
eStatusMAF_t circBuffer_Init(pHandleCircBuffer const pMe, const size_t size)
{
    assert(NULL != pMe);
    assert(MAX_CIRCULAR_BUFFER_SIZE > size);

    eStatusMAF_t status = e_SUCCESS;

    pMe->head = 0 ;
    pMe->tail = -1 ;
    pMe->numElems = 0;
    pMe->circBufSize = size;
    static_ResetBuf(pMe);

    return status;
}

/**
 * @brief Push data into circular buffer
 * 
 * @param pMe : Handle to circular buffer
 * @param data : Data to push to circular buffer
 * @return eStatusMAF_t : e_SUCCESS on success, e_OVERWRITE if data was overwritten
 */
eStatusMAF_t circBuffer_Enqueue(pHandleCircBuffer const pMe, const int16_t data)
{
    assert(NULL != pMe);
    eStatusMAF_t status = e_SUCCESS;

    if(circBuffer_IsFull(pMe))
    {
        status = e_OVERWRITE;
        pMe->numElems--; ///> Cap numElements here by decrementing 
    }
    pMe->tail = ((++(pMe->tail)) % (pMe->circBufSize)) ;

    pMe->buf[pMe->tail] = data;
    pMe->numElems++;

    return status;
}

/**
 * @brief deque data into circular buffer
 * 
 * @param pMe : Handle to circular buffer
 * @param pData : Pointer to data, to be filled up from deque circular buffer 
 * @return eStatusMAF_t : e_SUCCESS on success
 */
eStatusMAF_t circBuffer_Dequeue(pHandleCircBuffer const pMe, int16_t* pData)
{
    assert(NULL != pMe);
    eStatusMAF_t status = e_SUCCESS;

    if(circBuffer_IsEmpty(pMe))
    {
        status = e_FAIL;
    }
    else
    {
        *pData = pMe->buf[pMe->head] ;
        pMe->buf[pMe->head] = 0 ;

        pMe->head = ((++(pMe->head)) % (pMe->circBufSize)) ;

        pMe->numElems--;
    }
    return status;
}

/**
 * @brief peek data into circular buffer
 * 
 * @param pMe : Handle to circular buffer
 * @param pData : Pointer to data, to be filled up from peeked circular buffer 
 * @return eStatusMAF_t : e_SUCCESS on success 
 */
eStatusMAF_t circBuffer_Peek(pHandleCircBuffer const pMe, int16_t* pData)
{
    assert(NULL != pMe);
    eStatusMAF_t status = e_SUCCESS;

    if(circBuffer_IsEmpty(pMe))
    {
        status = e_FAIL;
    }
    else
    {
        *pData = pMe->buf[pMe->head] ;
    }
    return status;
}

/**
 * @brief function to get oldest entry in circular buffer
 * 
 * @param pMe : Handle to circular buffer
 * @param pData : Pointer to data, filled with oldest data from circular buffer 
 * @return eStatusMAF_t 
 */
eStatusMAF_t circBuffer_GetOldestData(pHandleCircBuffer const pMe, int16_t* pData)
{
    assert(NULL != pMe);
    eStatusMAF_t status = e_SUCCESS;

    if(circBuffer_IsEmpty(pMe))
    {
        status = e_FAIL;
    }
    else
    {
        int tempIter = (pMe->tail + 1) % (pMe->circBufSize) ;
        *pData = pMe->buf[tempIter] ;
    }
    return status;
}

/**
 * @brief function to get number of elements currently present in circular buffer
 * 
 * @param pMe : Handle to circular buffer
 * @return size_t : NUmber of elements present in circular buffer
 */
size_t circBuffer_GetNumElements(pHandleCircBuffer const pMe)
{
    return pMe->numElems ;
}


