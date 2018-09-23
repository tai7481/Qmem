/*William Tai
23 September 2018
CS270, Fall 2018
HW#3
*/

#include <stdio.h>

#ifndef QMEM_H_INCLUDED
#define QMEM_H_INCLUDED

//Allocation Functions
int qmem_alloc(unsigned num_bytes, void ** rslt);
int qmem_allocz(unsigned num_bytes, void ** rslt);
int qmem_allocv(unsigned num_bytes, int mark, void ** rslt);

//Deallocation Functions
int qmem_free(void ** rslt);

//Utility Functions
int qmem_cmp(void * p1, void * p2, int * diff);
int qmem_cpy(void * dat, void * src);
int qmem_scrub(void * data);
int qmem_scrubv(void * data, int mark);
int qmem_size(void * data, unsigned * rslt);
int qmem_stats(unsigned long * num_allocs, unsigned long * num_bytes_allocated);


#endif // QMEM_H_INCLUDED
