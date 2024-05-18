void shift_swap(int* list, int low, int high) {
    int tmp = list[high];

    for (int i=high; i>low; i--) {
        list[i] = list[i-1];
    }
    list[low] = tmp;
}

void quick_sort(int* list, int low, int high, int length) {
    int pivot_index = low;

    // if only 1 element is left; OR if only 2 elements are left, they are sured to be already sorted from previous iteration
    if (high - low == 0 || high - low == 1) return;

    for (int i=low; i<high; i++) {
        if (list[pivot_index] > list[i]) {
            shift_swap(list, pivot_index, i);
            pivot_index++;
        }
    }
    
    //print_list(list,length);
    quick_sort(list, low, pivot_index, length);  // left of pivot
    quick_sort(list, pivot_index+1, high, length); // right of pivot
}