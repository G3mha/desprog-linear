#include <stdlib.h>

#include "queue_int.h"

struct _queue_int {
    int capacity;
    int *data;
    int begin;
    int end;
    int size;
};

queue_int *queue_int_new(int capacity) {
    queue_int *q = malloc(sizeof(queue_int));
    q->capacity = capacity;
    q->data = malloc(capacity * sizeof(int));
    q->begin = capacity - 1;
    q->end = 0;
    q->size = 0;
    return q;
}

void queue_int_delete(queue_int **_q) {
    queue_int *q = *_q;
    free(q->data);
    free(q);
    *_q = NULL;
}

int queue_int_empty(queue_int *q) {
    return q->size == 0;
}

int queue_int_full(queue_int *q) {
    return q->size == q->capacity;
}

void queue_int_put(queue_int *q, int value) {
    q->data[q->end] = value;
    q->end = (q->end + 1) % q->capacity;
    q->size++;
}

int queue_int_get(queue_int *q) {
    q->size--;
    q->begin = (q->begin + 1) % q->capacity;
    return q->data[q->begin];
}

int queue_int_maxget(queue_int *q) {
    // gets the maximum value in the queue
    int max = q->data[q->begin];
    for (int i = 0; i < q->size; i++) {
        int index = (q->begin + i) % q->capacity;
        if (q->data[index] > max) {
            max = q->data[index];
        }
    }
    // and removes it from the queue
    for (int i = 0; i < q->size; i++) {
        int index = (q->begin + i) % q->capacity;
        if (q->data[index] == max) {
            q->data[index] = q->data[q->begin];
            q->data[q->begin] = max;
            break;
        }
    }
    return queue_int_get(q);
}

int main(void) {
    // test queue_int_maxget
    queue_int *q = queue_int_new(5);
    queue_int_put(q, 1);
    queue_int_put(q, 2);
    queue_int_put(q, 3);
    queue_int_put(q, 4);
    queue_int_put(q, 5);
    printf("%d\n", queue_int_maxget(q));
    printf("%d\n", queue_int_maxget(q));
    printf("%d\n", queue_int_maxget(q));
    printf("%d\n", queue_int_maxget(q));
    printf("%d\n", queue_int_maxget(q));
}