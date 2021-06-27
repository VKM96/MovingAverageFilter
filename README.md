Moving Average Filter Implementation                      {#mainpage}
============
    This is a simple Moving Average Filter Implementation for embedded systems.

**Code Structure**

1. Source files are present in @ref Src
2. Interface files are present in @ref inc
3. PLease refer doxygen generated HTML documentation in the Doc/html subfolder for implementation details
4. The function entry point is @ref Main.c

**Usage**

1. Initialization of the MAF is achieved through @ref filter_Init in @ref MovingAvgFilter.h
2. @ref filter_Init takes sample size as input, please ensure that is lesser than, or equal to @ref MAX_CIRCULAR_BUFFER_SIZE

**Modification**

1. Resize @ref MAX_CIRCULAR_BUFFER_SIZE so that it is close to filter sample size required. 

**Permissions**

1. Please refer to the LICENSE file 