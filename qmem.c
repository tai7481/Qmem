/*William Tai
23 September 2018
CS270, Fall 2018
HW#3*/

#include <stdio.h>
#include <stdlib.h>
#include "qmem.h"

struct Q
{
    int Index;
    char Data[256];
    Q * next;
};
typedef struct Q * QPtr = NULL;

//Function Implementations
int qmem_alloc(unsigned num_bytes, void ** rslt)
{
    int ErrorCode;

    if (rslt == NULL)
    {
        QPtr = (struct Q*) malloc (sizeof(struct Q));
        QPtr -> next = NULL;
        ErrorCode =  0;
    }
    else if (rslt != NULL)
    {
        ErrorCode = qmem_alloc(sizeof(struct Q), (void **) &QPtr);
    }
    else
        ErrorCode = -2;     //default return if neither allocation or detection is done

    return ErrorCode;
}

int qmem_allocz(unsigned num_bytes, void ** rslt)
{
    int ErrorCode;

    if (rslt == NULL)
    {
        QPtr = (struct Q*) malloc (sizeof(struct Q));
        QPtr -> next = NULL;
        for (int i = 0; i < 256; i++)
        {
            QPtr -> Data[i] = '0';
        }
        ErrorCode =  0;
    }
    else if (rslt != NULL)
    {
        ErrorCode = qmem_alloc(sizeof(struct Q), (void **) &QPtr);
    }
    else
        ErrorCode = -2;     //default return if neither allocation or detection is done

    return ErrorCode;
}
int qmem_allocv(unsigned num_bytes, int mark, void ** rslt);
int qmem_free(void ** rslt);
int qmem_cmp(void * p1, void * p2, int * diff);
int qmem_cpy(void * dat, void * src);
int qmem_scrub(void * data);
int qmem_scrubv(void * data, int mark);
int qmem_size(void * data, unsigned * rslt);
int qmem_stats(unsigned long * num_allocs, unsigned long * num_bytes_allocated);
