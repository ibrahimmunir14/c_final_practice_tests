#include "binaryheap.h"
#include <assert.h>
#include <string.h>

/* Note: length is the number of elements to heapsort
 *       heap_size is the size of heap, originally length+1, because heap[0] is NULL
 */

/*allocate memory in the heap for a node_heap type element and returns a pointer to the new node_heap*/

node_heap *allocate_node_heap(void)
{
    node_heap *node = (node_heap *) malloc(sizeof(node_heap));
    if (!node) {
        perror("malloc failed in allocate_node_heap");
        exit(EXIT_FAILURE);
    }
    return node;
}

/*initialise the heap array elements*/

void initial_heap(node_heap **heap, char* sequence)
{
    assert(heap);
    // heap[0] is left empty
    heap[0] = NULL;
    int pos = 1;
    while (*sequence) {
        node_heap *node = allocate_node_heap();
        node->key = sequence;
        node->position = pos;
        heap[pos] = node;
        pos++;
        sequence++;
    }
}


/*print every element of the heap array*/
void print_elem_heap(node_heap **heap, int length)
{
    assert(heap);
    for (int i = 1; i <= length; i++) {
        printf("%c ", *heap[i]->key);
    }
    printf("\n");
    for (int i = 1; i <= length; i++) {
        printf("%i ", heap[i]->position);
    }
    printf("\n");
}

/* returns the index in the heap array where the parent is allocated for the index passed as argument*/

int parent(int index)
{
    return div(index, 2).quot;
}

/* returns the index in the heap array where the left child is allocated for the index passed as argument*/

int left_child(int index)
{
    return index * 2;
}

/* returns the index in the heap array where the right child is allocated for the index passed as argument*/

int right_child(int index)
{
    return 1 + (index * 2);
}

/* exchange node_heap node1 to node_heap node2*/ 

void swap(node_heap *node1, node_heap *node2)
{
    assert(node1 && node2);
    node_heap *temp = allocate_node_heap();
    temp->position = node1->position;
    temp->key = node1->key;
    node1->position = node2->position;
    node1->key = node2->key;
    node2->position = temp->position;
    node2->key = temp->key;
    free_node(temp);
}

/*Moves down the value of the heap[current] so the subtree rooted at index "current" satisfies with the max-heap property*/ 

void max_heapify(node_heap **heap, int current, int heap_size)
{
    assert(heap);
    int left = left_child(current);
    int right = right_child(current);
    node_heap *curr = heap[current];
    if (left > heap_size && right > heap_size) { // leaf, bottom layer
        return;
    }
    if (right > heap_size) { // has left child only, above bottom layer
        if (*curr->key < *heap[left]->key) swap(curr, heap[left]);
        return;
    }
    // current node has both children
    if (*curr->key < *heap[left]->key || *curr->key < *heap[right]->key) { // not max_heap
        int largestChildIndex = *heap[right]->key > *heap[left]->key ? right : left;
        node_heap *largestChild = heap[largestChildIndex];
        swap(curr, largestChild);
        max_heapify(heap, largestChildIndex, heap_size);
        return;
    }
    // last case: both children, already max heap -> return
}

/*it orders the heap so the ordered heap complies the max-heap property*/

void build_max_heap(node_heap **heap, int heap_size)
{
    for (int i  = heap_size; i > 0; i--) {
        max_heapify(heap, i, heap_size);
    }
}

/*starting from a max-heap ordered array, it moves the largest item from the heap and it into the array position left as the heap shrinks*/

void heapsort(node_heap **heap, int length)
{
   while (heap[length]) {
       swap(heap[1], heap[length]);
       length --;
       max_heapify(heap, 1, length);
   }
    
}

/*free the memory allocated by a node_heap type element in the heap*/

void free_node(node_heap *node)
{
    if (!node) free(node);
}

/*free the memory allocated in the heap array*/

void free_heap(node_heap **heap, int length)
{
    if (heap) {
        for (int i = 1; i <= length; i++) {
            if (heap[i]) free(heap[i]);
        }
        free(heap);
    }
}