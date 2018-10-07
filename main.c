/*William Tai
23 September 2018
CS270, Fall 2018
HW#3*/

//This is a driver/test program for the
//qmem library

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "qmem.h"

int main()
{
    int Code = -100;
    void *result = NULL;

    Code = qmem_alloc(50, (void**)&result);
    printf("\nAllocation Error Code : %d\n", Code);
    Code = qmem_free((void**) &result);
    printf("Free Error Code : %d\n", Code);

    return 0;
}
