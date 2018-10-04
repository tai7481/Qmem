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
    void *result;

    Code = qmem_alloc(50, &result);
    printf("\nError Code : %d", Code);

    return 0;
}
