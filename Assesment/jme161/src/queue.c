#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

#include "queue.h"


#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)



/*
 * Queue - the abstract type of a concurrent queue.
 * You must provide an implementation of this type 
 * but it is hidden from the outside.
 */
typedef struct QueueStruct {
    sem_t mutex;
    sem_t items;
    sem_t spaces;

    pthread_mutex_t lockTail;
    pthread_mutex_t lockHead;

    // struct QueueStruct *next;
    // void *value;

    struct QueueStruct *head;
    struct QueueStruct *tail;

    void *value;
    int size;
    int count;
    struct QueueStruct *front;
    struct QueueStruct *rear;
    struct QueueStruct *next;
} Queue;


/**
 * Allocate a concurrent queue of a specific size
 * @param size   - The size of memory to allocate to the queue
 * @return queue - Pointer to the allocated queue
 */
Queue *queue_alloc(int size) 
{
    Queue *queue = (Queue*)malloc(sizeof(Queue) * size);
    queue->next = queue;
    queue->front = queue;
    queue->rear = queue;
    queue->size = size;
    queue->count = 0;
    queue->value = malloc(sizeof(void));

    // queue->front = queue->rear = queue->next = NULL;
    // queue->value = 0;

    pthread_mutex_init(&queue->lockHead, NULL);
    pthread_mutex_init(&queue->lockTail, NULL);

    sem_init(&queue->mutex, 0, 1);
    sem_init(&queue->items, 0, 0);
    // sem_init(&queue->spaces, 0, size-1); 
    sem_init(&queue->spaces, 0, 1); 

    return queue;
}


void free_list(Queue *list) 
{

    for (Queue *l = list; l != NULL;) {
        Queue *next = l->next;
        free(l);

        l = next;
    }
}


/**
 * Free a concurrent queue and associated memory 
 *
 * Don't call this function while the queue is still in use.
 * (Note, this is a pre-condition to the function and does not need
 * to be checked)
 * 
 * @param queue - Pointer to the queue to free
 */
void queue_free(Queue *queue) 
{
    // free_list(queue->front);
    // free(queue);
}


/**
 * Place an item into the concurrent queue.
 * If no space available then queue will block
 * until a space is available when it will
 * put the item into the queue and immediatly return
 *  
 * @param queue - Pointer to the queue to add an item to
 * @param item  - An item to add to queue. Uses void* to hold an arbitrary
 *               type. User's responsibility to manage memory and ensure
 *               it is correctly typed.
 */

int a = 0;


void queue_put(Queue *queue, void *item) 
{   
    // Invalid free() error fix !!!
    // Queue *queue_ = (Queue*)malloc(sizeof(Queue));

    if (a > queue->size) return;

    sem_wait(&queue->spaces);
    pthread_mutex_lock(&queue->lockTail);
    
    // queue_->value = item;
    // queue_->next = NULL;
    // queue_->size = queue->count;

    puts("In Puts");
    a++;
    // if (queue->rear == NULL) {
    //     queue->front = queue->rear = queue_;
    // } else {
    //     queue->rear->next = queue_;
    //     queue->rear = queue_;
    // }
    // printf("Hello the size:   %d\n", queue->count);
    // queue->count++;

    pthread_mutex_unlock(&queue->lockTail);
    sem_post(&queue->items);
}


/**
 * Get an item from the concurrent queue
 * 
 * If there is no item available then queue_get
 * will block until an item becomes avaible when
 * it will immediately return that item.
 * 
 * @param queue - Pointer to queue to get item from
 * @return item - item retrieved from queue. void* type since it can be 
 *                arbitrary 
 */
///// Need to signal to quit
void *queue_get(Queue *queue) 
{
    if (a > queue->size) return NULL;
    void *item = 0;

    sem_wait(&queue->items);
    pthread_mutex_lock(&queue->lockHead);

    // Queue *queue_ = queue->front;

    // queue->front = queue->front->next;
    // void *item = (void*)&queue->front->value;
    // free(queue_);
    // printf("%d\n", *(int*)queue->front->value);
    
    puts("In Gets");
    // printf("%d\n", *(int*)queue->front->value);


    pthread_mutex_unlock(&queue->lockHead);
    sem_post(&queue->spaces);

    // if (queue->count > queue->size) return NULL;

    return item;
}































// #define QUEUE_POISON1 ((void*)0xCAFEBAB5)

// typedef struct QueueStruct {
// 	struct QueueStruct *head;
// 	pthread_mutex_t head_lock;

// 	struct QueueStruct *tail;
// 	pthread_mutex_t tail_lock;

// 	struct QueueStruct *divider;
// } Queue;


// Queue *queue_alloc(int size)
// {
// 	Queue *root = 
// 		malloc(sizeof(Queue));
// 	pthread_mutex_init(&root->head_lock, NULL);
// 	pthread_mutex_init(&root->tail_lock, NULL);

// 	root->divider = NULL;
// 	root->head = root->divider;
// 	root->tail = root->divider;
// 	return root;
// }


// // void INIT_QUEUE_HEAD(struct queue_head *head)
// // {
// // 	head->next = QUEUE_POISON1;
// // }


//  void queue_put(Queue *queue, void *item)
// {
// 	// new->next = NULL;

// 	pthread_mutex_lock(&queue->tail_lock);
// 	queue->tail = (Queue*)item;
// 	pthread_mutex_unlock(&queue->tail_lock);
// }


// void *queue_get(Queue *queue)
// {
// 	Queue *head, *next = NULL;

	// while (1) {
	// 	pthread_mutex_lock(&queue->head_lock);
	// 	head = queue->head;
	// 	// next = head->next;
	// 	if (next == NULL) {
	// 		pthread_mutex_unlock(&queue->head_lock);
	// 		return NULL;
	// 	}
	// 	queue->head = next;
	// 	pthread_mutex_unlock(&queue->head_lock);
		
	// 	if (head == queue->divider) {
	// 		queue_put(head, queue);
	// 		continue;
	// 	}

		// queue->head = QUEUE_POISON1;
	// }
// }