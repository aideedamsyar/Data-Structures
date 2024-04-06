#include <stdio.h>
#include <stdlib.h>

struct CircularQueueStruct {
    int* key;
    int front; // index of front
    int rear; // index of rear
    int size; // currrent size
    int max_queue_size;
};

typedef struct CircularQueueStruct* CircularQueue;

CircularQueue MakeEmpty(int max);
int IsEmpty(CircularQueue Q);
int IsFull(CircularQueue Q);
void Dequeue(CircularQueue Q);
void Enqueue(CircularQueue Q, int x);
void PrintFirst(CircularQueue Q);
void PrintRear(CircularQueue Q);
void DeleteQueue(CircularQueue Q);

int main(int argc, char* argv[]) {
    char command;
    FILE *input;
    CircularQueue queue;
    int queueSize;
    int tmpNum;

    input = fopen(argv[1], "r");

    while(1) {
        command = fgetc(input);
        if (feof(input)) break;
        switch (command) {
            case 'n': 
                fscanf(input, "%d", &queueSize);
                queue = MakeEmpty(queueSize);
                break;
            case 'e':
                fscanf(input, "%d", &tmpNum);
                Enqueue(queue, tmpNum);
                break;
            case 'd':
                Dequeue(queue);
                break;
            case 'f':
                PrintFirst(queue);
                break;
            case 'r':
                PrintRear(queue);
                break;
            default:
                break;
        }
    }
    DeleteQueue(queue);
}

CircularQueue MakeEmpty(int max) {
    CircularQueue queue = malloc(sizeof(struct CircularQueueStruct));
    if (!queue || !(queue->key = (int*)malloc(max * sizeof(int)))) {
        // If memory allocation fails, print error and return NULL
        printf("Memory allocation failed\n");
        return NULL;
    }    
    queue->size = 0;
    queue->max_queue_size = max;
    queue->front = 1;
    queue->rear = 0;

    return queue;
}

int IsEmpty(CircularQueue Q) {
    return (Q->size == 0);
}

int IsFull(CircularQueue Q) {
    return (Q->size == Q->max_queue_size);
}

void Dequeue(CircularQueue Q) {
    int y = -1;
    if (IsEmpty(Q)) {
        printf("Dequeue failed : Queue is Empty!\n");
        return;
    } else {        
        y = Q->key[Q->front];
        Q->front = (Q->front + 1) % Q->max_queue_size;
        printf("Dequeue %d\n", y);
        Q->size--;
    }
}

void Enqueue(CircularQueue Q, int x) {
    if (IsFull(Q)) {
        printf("Enqueue failed : Queue is Full!\n");
        return;
    } else {
        Q->size++;
        Q->rear = ((Q->rear+1) % Q->max_queue_size);
        Q->key[Q->rear] = x;
        printf("Enqueue %d\n", x);
    }
}

void PrintFirst(CircularQueue Q) {
    if (IsEmpty(Q)) {
        printf("Queue is Empty!\n");
        return;
    } else {
        printf("Element in the front : %d\n", Q->key[Q->front]);
    }
}

void PrintRear(CircularQueue Q) {
    if (IsEmpty(Q)) {
        printf("Queue is Empty!\n");
        return;
    } else {
        printf("Element in the rear : %d\n", Q->key[Q->rear]);
    }
}

void DeleteQueue(CircularQueue Q) {
    free(Q->key);
    free(Q);
}