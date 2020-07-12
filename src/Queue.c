#include "Queue.h"


Queue *queueNew(void (*deleteFunc)(void *), char *(*printFunc)(void *));


QueueNode *queueNodeNew(void *data);


void queueClear(Queue *queue);


void queueFree(Queue *queue);


void enqueue(Queue *queue, void *data);


void *queuePeekFront(const Queue *queue);


void *queuePeekBack(const Queue *queue);


void *dequeue(Queue *queue);


unsigned int queueGetLength(const Queue *queue);


bool queueIsEmpty(const Queue *queue);


char *queueFrontToString(const Queue *queue);


char *queueBackToString(const Queue *queue);


void queuePrintFront(const Queue *queue);


void queuePrintBack(const Queue *queue);


char *queueToString(const Queue *queue);


void queuePrint(const Queue *queue);


void queueMap(Queue *queue, void (*func)(QueueNode *));

