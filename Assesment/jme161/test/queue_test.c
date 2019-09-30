#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define NUM_THREADS 16
#define N 10 //1000000

typedef struct {
    int value;
} Task;


void *doSum(void *arg) {
    int sum = 0;
    Queue *queue = (Queue*)arg;
    puts("here");
    // printf("hi %d\n", *(int*)queue->);
    Task *task = (Task*)queue_get(queue);
    puts("there");

    while (task) {
        sum += task->value;
        printf("%d\n", sum);
        free(task);

        task = (Task*)queue_get(queue);
    }

    pthread_exit((void*)(intptr_t)sum);
}



int main(int argc, char **argv) {

    // int i, sum;

    // pthread_t thread[NUM_THREADS];
    Queue *queue = queue_alloc(12);

    Task *task = (Task*)queue_get(queue);


    printf("2: %d\n", task->value);

    //
    // // puts("1");
    // for (i = 0; i < NUM_THREADS; ++i) {
    //     pthread_create(&thread[i], NULL, doSum, queue);
    //     printf("%d\n", i);
    // }
    // // puts("2");

    // // int expected = 0;
    // // for (i = 0; i < N; ++i) {
    // //     Task *task = (Task*)malloc(sizeof(Task));
    // //     task->value = i;



    // //     queue_put(queue, task);
    // //     expected += i;
    // // }


    // // for (i = 0; i < NUM_THREADS; ++i) {
    // //     queue_put(queue, NULL);
    // // }

    // intptr_t value;
    // sum = 0;
    // for (i = 0; i < NUM_THREADS; ++i) {
    //     pthread_join(thread[i], (void**)&value);
    //     sum += value;
    // }

    // queue_free(queue);

    // printf("total sum: %d, expected sum: inf\n", (int)sum);
    // // printf("total sum: %d, expected sum: %d\n", (int)sum, expected);

    return 0;
}
