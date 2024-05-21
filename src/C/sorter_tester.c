#include "random_generator.h"
//#include "bubble_sort.h"
#include "merge_sort.h"

int main() {
    int len = 100, c=0;
    int* manual_list = (int*) malloc(len * sizeof(int));
    int* sorted;

    for (int i=len; i>0; i--) {
        *(manual_list+c) = i;
        c++;
    }

    print_list(manual_list, len);
    //bubble_sort(manual_list, len);
    sorted = merge_sort(manual_list, len);
    print_list(sorted, len);

    check_if_sorted(sorted, len);

    free(manual_list);
    free(sorted);
    return 0;
}