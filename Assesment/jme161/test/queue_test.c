#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

<<<<<<< HEAD
#define NUM_THREADS 1//16
#define N 5//1000000
=======
#define NUM_THREADS 16
#define N 1000000
>>>>>>> 5415ca98b6919f90c6bc91368897e216ea6d6f3b


typedef struct {
    int value;
} Task;


void *doSum(void *arg) {
    int sum = 0;
    Queue *queue = (Queue*)arg;
    Task *task = (Task*)queue_get(queue);
    while (task) {
        sum += task->value;
        free(task);
        task = (Task*)queue_get(queue);
    }

    pthread_exit((void*)(intptr_t)sum);
}


int main(int argc, char **argv) {

    int i, sum;

    pthread_t thread[NUM_THREADS];
    Queue *queue = queue_alloc(NUM_THREADS);

    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&thread[i], NULL, doSum, queue);
    }

    int expected = 0;
    for (i = 0; i < N; ++i) {
        Task *task = (Task*)malloc(sizeof(Task));
        task->value = i;
        
        queue_put(queue, task);
        
        expected += i;
    }

    for (i = 0; i < NUM_THREADS; ++i) {
        queue_put(queue, NULL);
    }

    
    intptr_t value;
    sum = 0;
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thread[i], (void**)&value);
        sum += value;
    }
    
    queue_free(queue);

    printf("total sum: %d, expected sum: %d\n", (int)sum, expected);

    return 0;
}
