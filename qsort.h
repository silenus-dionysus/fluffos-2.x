#ifndef QSORT_H
#define QSORT_H

/*
 * qsort.c
 */
class QuickSort {
public:
void quickSort (void *, int, int, int (*) (void *, void *));
};

extern QuickSort globalQuickS;
#endif
