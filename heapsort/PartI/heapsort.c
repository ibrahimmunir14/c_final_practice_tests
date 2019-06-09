#include "binaryheap.h"


int main(int argc, char **argv){
    if (argc != 2) {
        printf("I need a string sequence to heapsort!");
        return EXIT_FAILURE;
    }
    char *sequence = argv[1];
    int length = 0;
    while (sequence[length]) {
        length++;
    }
    printf("Length: %i\n", length);
    node_heap **heap = malloc((1+length) * sizeof(node_heap *));
    if (!heap) {
        perror("malloc failed in main");
        return EXIT_FAILURE;
    }

    initial_heap(heap, sequence);
    print_elem_heap(heap, length);

    build_max_heap(heap, length);
    print_elem_heap(heap, length);

    heapsort(heap, length);
    print_elem_heap(heap, length);

    free_heap(heap, length);
 return EXIT_SUCCESS;
}