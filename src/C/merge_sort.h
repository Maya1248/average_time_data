#ifndef STDLIB_H
#include <stdlib.h>
#endif

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int* merge_left_and_right(int* left_half, int* right_half, int left_length, int right_length) {
    int i=0;
    int j=0;
    int c=0;

    int* merged_list = (int*) malloc((left_length + right_length) * sizeof(int));

    while (i < left_length && j < right_length) {

        if (*(left_half+i) < *(right_half+j)) {
            *(merged_list+c) = *(left_half+i);
            
            i++;
            c++;
        } else {
            *(merged_list+c) = *(right_half+j);

            j++;
            c++;
        }   
    }

    // There are 4 possible outcomes
    // 1: i and j are both less than their lengths -> dont touch anything
    // 2: i and j have both reached their lengths conviniently at the same time -> dont touch anything, the following IFs will do nothing
    // 3: i has reached its end, but j has not -> the IF will fill out the merged_list with the remaining half (as it is on its own already sorted)
    // 4: same as 3. but for j ending and i not ending...

    if (i < left_length && !(j < right_length)) {
        while (i < left_length) {
            *(merged_list+c) = *(left_half+i);

            i++;
            c++;
        }
    }
    if (!(i < left_length) && j < right_length) {
        while (j < right_length) {
            *(merged_list+c) = *(right_half+j);

            j++;
            c++;
        }
    }

    free(left_half);
    free(right_half);
    return merged_list;
}

int* merge_sort(int* list, int length) {
    
    // Perform recursion step 2.
    // For intuitive process pretend we got left_half right now as list.
    // We have 3 options that can exist.
    // 1: List is of size 1 -> return it.
    // 2: List is of size 2 -> perform comparison and return it.
    // 3: List is larger than size 3 -> go forth with recursion.
    if (length == 1) {
        return list;
    } else if (length == 2) {
        if (*(list+0) > *(list+1)) {
            swap(list+0, list+1);
        }
        return list;
    }


    // Create new lists for each half
    int* left_half = (int*) malloc((length / 2) * sizeof(int));
    int* right_half = (int*) malloc((length - (length / 2)) * sizeof(int));

    // Fill out the lists
    for (int i=0; i<length/2; i++) {
        *(left_half+i) = *(list+i);
    }
    for (int i=length/2; i<length - length/2; i++) {
        *(right_half+i) = *(list+i);
    }

    // Perform recursion step 1.
    left_half = merge_sort(left_half, length/2);
    right_half = merge_sort(right_half, length - length/2);

    return merge_left_and_right(left_half, right_half, length/2, length - length/2);
}