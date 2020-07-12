#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************
 * STRUCTURES *
 **************/

/*
 * This queue implementation is a "Linked List Queue" (often abbreviated to "Linked Queue"),
 * which uses a linked list to store a collection of elements.
 * More specifically, this implementation is a "Doubly Linked Queue", since this structure
 * is backed by a doubly-linked list.
 *
 * This approach, in contrast to the "Circular Array Queue", is typically more memory efficient
 * for large queues (because memory is allocated per-element instead of having lots of
 * empty space in an array) but slightly less runtime efficient on average due to the
 * expensiveness of allocating memory every time a new item is enqueued.
 *
 * This structure represents a node in the linked queue that holds a single piece of
 * abstracted (void *) data.
 */
typedef struct queueNode {
	void *data;
	struct queueNode *previous;
	struct queueNode *next;
} QueueNode;

/*
 * Metadata top of the queue. 
 * Contains the function pointers for working with the abstracted list data.
 */
typedef struct queueHead {
	QueueNode *front;
	QueueNode *back;
	unsigned int length;
	void (*deleteData)(void *);	// Function pointer to free an element in the queue
	char *(*printData)(void *);	// Function pointer to create a string from a queue element
} Queue;


/*************
 * FUNCTIONS *
 *************/

/*
 * Function to initialize the Queue metadata head to the appropriate function pointers.
 * Allocates memory to the struct, unless any of the function pointers are NULL. In this
 * case, NULL is returned instead and no memory is allocated.
 *
 * The Queue provides an interface to a generic collection of data. The two 
 * function pointers allow the struct to print and delete its data.
 * The (void *) arguments are to be casted into their proper data type (i.e. whatever
 * data type the tree will be holding) and do as follows:
 *
 *  char *printFunc(void *toPrint)  : return a string representation of `toPrint`
 *  void deleteFunc(void *toDelete) : free all memory associated with `toDelete`
 *
 * Examples of these functions are provided for string (char *) data in the README.
 */
Queue *queueNew(void (*deleteFunc)(void *), char *(*printFunc)(void *));


/*
 * Allocates memory for a new QueueNode struct and returns a pointer to it.
 */
QueueNode *queueNodeNew(void *data);


/*
 * Removes every element from a Queue without deleting the queue itself.
 */
void queueClear(Queue *queue);


/*
 * Frees all memory associated with a Queue, including the queue itself.
 */
void queueFree(Queue *queue);


/*
 * Adds the data to the back of the queue.
 */
void enqueue(Queue *queue, void *data);


/*
 * Returns the front of the queue after removing it from the queue.
 */
void *dequeue(Queue *queue);


/*
 * Returns the front of the queue without removing it.
 */
void *queuePeekFront(const Queue *queue);


/*
 * Returns the back of the queue without removing it.
 */
void *queuePeekBack(const Queue *queue);


/*
 * Returns the number of elements in the queue.
 */
unsigned int queueGetLength(const Queue *queue);


/*
 * Returns true if the Queue contains 0 elements, and false otherwise.
 */
bool queueIsEmpty(const Queue *queue);


/*
 * Returns a string representing the element at the front of the Queue using the queue's
 * `printData` function pointer to create the string.
 *
 * The string msut be freed by the calling function after use.
 */
char *queueFrontToString(const Queue *queue);


/*
 * Returns a string representing the element at the back of the Queue using the queue's
 * `printData` function pointer to create the string.
 *
 * The string msut be freed by the calling function after use.
 */
char *queueBackToString(const Queue *queue);


/*
 * A convenient alias for printing the string returned by `queueFrontToString(queue)`
 * and then freeing the string that was created after printing it.
 * A newline is printed after the queue-element-string is done printing.
 */
void queuePrintFront(const Queue *queue);


/*
 * A convenient alias for printing the string returned by `queueBackToString(queue)`
 * and then freeing the string that was created after printing it.
 * A newline is printed after the queue-element-string is done printing.
 */
void queuePrintBack(const Queue *queue);


/*
 * Returns a string representing the Queue using the queue's `printData` function pointer
 * to create the string, starting from the front of the queue and working towards the back.
 *
 * The string must be freed by the calling function after use.
 */
char *queueToString(const Queue *queue);


/*
 * A convenient alias for printing the string returned by `queueToString(queue)`
 * and then freeing the string that was created after printing it.
 * A newline is printed after the queue-string is done printing.
 */
void queuePrint(const Queue *queue);


/*
 * Execute a function `func` on each node in the queue
 * starting from the front and working towards the back.
 */
void queueMapNode(Queue *queue, void (*func)(QueueNode *));


/*
 * Execute a function `func` on each data item in the queue
 * starting form the front and working towards the back.
 */
void queueMapData(Queue *queue, void (*func)(void *));

#endif	// QUEUE_H

