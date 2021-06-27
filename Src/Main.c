/**
 * @file Main.c
 * @author vishal K
 * @brief 
 * @version @ref VERSION
 * @date 2020-12-20
 * @bug No known bugs at the time of development
 * 
 */

#include <stdio.h>
#include <stdint.h>
#include "MovingAvgFilter.h"


/**
 * @brief Array for demonstrating implementation
 * 
 */
const int testIntArr[20] = {1,2,3,4,5,6,7,8,9,10,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1};

/**
 * @brief Function entry point, Initialization and logging of logger demonstrated
 * 
 * 
 * @return int 
 */
int main()
{
    ///> Make a filter struct here and assign its address to the filter handle
    sAvgFilter_t movingAvgFilter;
    pHandleFilter filterHandle = &(movingAvgFilter);

    filter_Init(filterHandle,4);

    for(int i=0 ; i<20 ; i++)
    {
        ///> Insert data in and print average at every stage
        filter_DataIn(filterHandle,testIntArr[i]);
        printf("%d\n",filter_GetAvg(filterHandle));

    }
    return 0;

}