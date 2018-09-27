/*William Tai
23 September 2018
CS270, Fall 2018
HW#3*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "qmem.h"

//Function Implementations
int qmem_alloc(unsigned num_bytes, void ** rslt)
{
    int ErrorCode = -2;

    if (num_bytes < 0)  //checks if num_bytes is
    {
        printf("Memory Allocation Error\n");
        ErrorCode = -1;
    }
    else
    {
        if (rslt == NULL)
        {
            (*rslt) = (void*) malloc (num_bytes);
            ErrorCode =  0;
        }
        else
            ErrorCode = -2;     //default return if neither allocation or detection is done
    }
    return ErrorCode;
}

int qmem_allocz(unsigned num_bytes, void ** rslt)
{
    int ErrorCode = -2;

    if (num_bytes < 0)  //checks if num_bytes is
    {
        printf("Memory Allocation and Initialization Error\n");
        ErrorCode = -1;
    }
    else
    {
        if (rslt == NULL)
        {
            (*rslt) = (void*) calloc (sizeof(*rslt), num_bytes);
            ErrorCode =  0;
        }
        else
            ErrorCode = -2;     //default return if neither allocation or detection is done
    }
    return ErrorCode;
}

int qmem_allocv(unsigned num_bytes, int mark, void ** rslt)
{
    int ErrorCode = -2;
    unsigned n = mark;
    unsigned lower8bits = n & 0xFF;

    if (num_bytes < 0)  //checks if num_bytes is
    {
        printf("Memory Allocation and Initialization Error\n");
        ErrorCode = -1;
    }
    else
    {
        if (rslt == NULL)
        {
            (*rslt) = (void*) calloc (lower8bits, num_bytes);
            ErrorCode =  0;
        }
        else
            ErrorCode = -2;     //default return if neither allocation or detection is done
    }
    return ErrorCode;
}

int qmem_free(void ** rslt)
{
    int ErrorCode = -2;

    if (rslt == NULL)
    {
        ErrorCode = -1;
    }
    else if (rslt != NULL)
    {
        free(*rslt);
        (*rslt) = NULL;
        ErrorCode = 0;
    }
    return ErrorCode;
}

int qmem_cmp(void * p1, void * p2, int * diff)
{
    int ErrorCode = 5;
    int i = 0;
    int Difference = 100;

    if (p1 == NULL)
    {
        ErrorCode = -1;
    }
    else if (p2 == NULL)
    {
        ErrorCode = -2;
    }
    else if (//p1 not allocated with qmem)
    {
        ErrorCode = -3;
    }
    else if (//p2 not allocated with qmem)
    {
        ErrorCode = -4;
    }
    else
    {
        for ( i = 0; i < sizeof(p1) && i < sizeof(p2); i++)
        {
            if (p1[i] != p2[i])
            {
                Difference = abs(&p1-&p2);
                ErrorCode = 0;
            }
            else
            {
                ErrorCode = 0;
                Difference = 0;
            }
        }
    }

    diff = &Difference;
    return ErrorCode;
}

int qmem_cpy(void * dst, void * src)
{
    int ErrorCode = -10;

    if (dst == NULL)
    {
        ErrorCode = -1;
    }
    else if (src == NULL)
    {
        ErrorCode = -2;
    }
    else if (//dst not allocated with qmem)
    {
        ErrorCode = -3;
    }
    else if (//src not allocated with qmem)
    {
        ErrorCode = -4;
    }
    else if (dst == src)
    {
        ErrorCode = -5;
    }
    else if (sizeof(dst) != sizeof(src))
    {
        ErrorCode = -6;
    }
    else
    {
        memcpy(&dst, &src, sizeof(src));
        ErrorCode = 0;
    }

    return ErrorCode;
}
int qmem_scrub(void * data);
int qmem_scrubv(void * data, int mark);
int qmem_size(void * data, unsigned * rslt);
int qmem_stats(unsigned long * num_allocs, unsigned long * num_bytes_allocated);
