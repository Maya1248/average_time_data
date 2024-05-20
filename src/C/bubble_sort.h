#ifndef COMMON_MICRO_METHODS_H
#define COMMON_MICRO_METHODS_H
#include "common_micro_methods.h"
#endif

void bubble_sort(int* list, int length) {
    int i=0;
    int j=0;

    while (i+1 < length) {

        while (j+1 < length) {
            if (list[j] > list[j+1]) {
                swap(&list[j], &list[j+1]);
            }

            j++;
        }
        
        i++;
        j=0;
    }
}