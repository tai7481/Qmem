/*William Tai
23 September 2018
CS270, Fall 2018
HW#3*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qmem.h"

//Global Variables to tracks qmem usage for
//Allocations and Initializations
int qmemcount = 0;
int qmemusage = 0;

//Array of pointers meant to keep track of qmem usage
void **qmem;

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
            qmem[qmemcount] = &(*rslt);
            qmemcount++;
            qmemusage++;
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
            qmem[qmemcount] = &(*rslt);
            qmemcount++;
            qmemusage++;
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
            (*rslt) = (void*) calloc(lower8bits, num_bytes);
            ErrorCode =  0;
            qmem[qmemcount] = &(*rslt);
            qmemcount++;
            qmemusage++;
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
        qmemcount--;
        qmemusage--;
    }
    return ErrorCode;
}

int qmem_cmp(void * p1, void * p2, int * diff)
{
    int ErrorCode = 5;
    int j = 0;
    int Difference = 100;

    if (p1 == NULL)
    {
        ErrorCode = -1;
    }
    else if (p2 == NULL)
    {
        ErrorCode = -2;
    }
    else if ((p1 != NULL && p2 != NULL))
    {
        if (p1 != p2)
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
    else if (p1 != NULL)
    {
        for (j = 0; j < qmemcount; j++)
        {
            if (p1 != qmem[j])
            {
                ErrorCode = -3;
            }
        }
        //continue
    }
    else if (p2 != NULL)
    {
        for (j = 0; j < qmemcount; j++)
        {
            if (p2 != qmem[j])
            {
                ErrorCode = -4;
            }
        }
    }
    diff = &Difference;
    return ErrorCode;
}

int qmem_cpy(void * dst, void * src)
{
    int ErrorCode = -10;
    int j = 0;

    if (dst == NULL)
    {
        ErrorCode = -1;
    }
    else if (src == NULL)
    {
        ErrorCode = -2;
    }
    else if (dst != NULL)
    {
        for (j = 0; j < qmemcount; j++)
        {
            if (dst != qmem[j])
            {
                ErrorCode = -3;
            }
        }
        //continue;
    }
    else if (src != NULL)
    {
        for (j = 0; j < qmemcount; j++)
        {
            if (src != qmem[j])
            {
                ErrorCode = -4;
            }
        }
        //continue;
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

int qmem_scrub(void * data)
{
    int ErrorCode = -3;
    void * temp = data;
    int j = 0;
    if (temp != NULL)
    {
        for (j = 0; j < qmemcount; j++)
        {
            if (temp != qmem[j])
            {
                ErrorCode = -2;
            }
        }
        //continue;
    }
    else if (temp == NULL)
    {
        ErrorCode = -1;
    }
    else
    {
        temp = calloc(temp, sizeof(temp));
        ErrorCode = 0;
    }
    return ErrorCode;
}

int qmem_scrubv(void * data, int mark)
{
    int ErrorCode = -3;
    int j = 0;
    unsigned n = mark;
    unsigned lower8bits = n & 0xFF;

    if (data == NULL)
    {
        ErrorCode = -1;
    }
    else if (data != NULL)
    {
        for (j = 0; j < qmemcount; j++)
        {
            if (data != qmem[j])
            {
                ErrorCode = -2;
            }
        }
    }
    else
    {
        void * temp = (void*)calloc (lower8bits, sizeof(data));
        data = temp;
        ErrorCode = 0;
    }
    return ErrorCode;
}

int qmem_size(void * data, unsigned * rslt)
{
    int ErrorCode = -4;
    int j = 0;
    int Result = 0;

    if (data == NULL)
    {
        ErrorCode = -1;
    }
    else if (rslt == NULL)
    {
        ErrorCode = -2;
    }
    else if (data != NULL)
    {
        for (j = 0; j < qmemcount; j++)
        {
            if (data != qmem[j])
            {
                ErrorCode = -3;
            }
        }
    }
    else
    {
        Result = sizeof(data);
        ErrorCode = 0;
    }
    rslt = &Result;
    return ErrorCode;
}

int qmem_stats(unsigned long * num_allocs, unsigned long * num_bytes_allocated)
{
    int ErrorCode = -3;
    int SizeAllocated = 0;
    int i = 0;

    if (num_allocs == NULL)
    {
        ErrorCode = -1;
    }
    else if (num_bytes_allocated == NULL)
    {
        ErrorCode = -2;
    }
    else
    {
        num_allocs = &qmemcount;
        for (i = 0; i <= qmemcount; i++)
        {
            SizeAllocated = SizeAllocated + sizeof(qmem[i]);
        }
        ErrorCode = 0;
    }
    return ErrorCode;
}

