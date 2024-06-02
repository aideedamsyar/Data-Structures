#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct* Heap;
struct HeapStruct {
    int capacity;
    int size;
    int *elements;
};

Heap CreateHeap(int heapSize);
void Insert(Heap heap, int value);
int Find(Heap heap, int value);
void DeleteMax(Heap heap);
void PrintHeap(Heap heap);
void FreeHeap(Heap heap);

int main(int argc, char* argv[]) {
    FILE *fi = fopen(argv[1], "r");
    char cv;
    Heap maxHeap;
    int value, MaxValue;

    while(fscanf(fi, " %c", &cv) == 1) {
        switch(cv) {
            case 'n':
                fscanf(fi, "%d", &value);
                maxHeap = CreateHeap(value);
                break;
            case 'i':
                fscanf(fi, "%d", &value);
                Insert(maxHeap, value);
                break;
            case 'd':
                DeleteMax(maxHeap);
                break;
            case 'f':
                fscanf(fi, "%d", &value);
                if (Find(maxHeap, value))
                    printf("%d is in the heap.\n", value);
                else
                    printf("%d is not in the heap.\n", value);
                break;  
            case 'p':
                PrintHeap(maxHeap);
                break;
        }
    }
    FreeHeap(maxHeap);
    return 0;
}

Heap CreateHeap(int heapSize) {
    Heap heap = malloc(sizeof(struct HeapStruct));
    if (heap == NULL) {
        printf("Error! Out of memory!\n");
        return NULL;
    }

    heap->capacity = heapSize;
    heap->elements = malloc(sizeof(int) * (heapSize + 1));

    if (heap->elements == NULL) {
        free(heap);
        printf("Error! Out of memory!\n");
        return NULL;
    }

    heap->size = 0;
    return heap;
}

int isFull(Heap heap) {
    return heap->size == heap->capacity;
}

int isEmpty(Heap heap) {
    return heap->size == 0;
}

int Find(Heap heap, int value) {
    for (int i = 1; i <= heap->size; i++) {
        if (heap->elements[i] == value) return 1;
    }
    return 0;
}

void Insert(Heap heap, int value) {
    if (isFull(heap)) {
        printf("Insertion Error : Max Heap is full!\n");
        return;
    }
    if (Find(heap, value)) {
        printf("%d is already in the heap.\n", value);
        return;
    }

    int i;
    for (i = ++heap->size; i > 1 && heap->elements[i / 2] < value; i /= 2) {
        heap->elements[i] = heap->elements[i / 2];
    }
    heap->elements[i] = value;

    printf("Insert %d\n", value);
}

void DeleteMax(Heap heap) {
    if (isEmpty(heap)) {
        printf("Deletion Error : Max Heap is empty!\n");
        return;
    }
    int lastElement = heap->elements[heap->size--];
    printf("Max Element %d is deleted.\n", heap->elements[1]);

    int i, child;

    for (i = 1; i * 2 <= heap->size; i = child) {
        child = i * 2;
        if (child != heap->size && heap->elements[child + 1] > heap->elements[child])
            child++;
            
        if (lastElement < heap->elements[child]) {
            heap->elements[i] = heap->elements[child];
        } else {
            break;
        }
    }
    heap->elements[i] = lastElement;


}

void PrintHeap(Heap heap) {
    if (isEmpty(heap)) {
        printf("Print Error : Max Heap is empty!\n");
    } else {
        for (int i = 1; i <= heap->size; i++) {
            printf("%d ", heap->elements[i]);
        }
        printf("\n");
    }
}

void FreeHeap(Heap heap) {
    if (heap != NULL) {
        free(heap->elements);
        free(heap);
    }
}
