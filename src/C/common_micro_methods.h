void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int check_if_sorted(int* list, int length) {
    for (int i=0; i<length-1; i++) {
        if (list[i] > list[i+1]) {
            printf("[-] List is not sorted...\n");
            return -1;
        }
    }
    return 0;
}