void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

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