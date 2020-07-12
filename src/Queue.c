#include "Queue.h"


Queue *queueNew(void (*deleteFunc)(void *), char *(*printFunc)(void *)) {
	if (deleteFunc == NULL || printFunc == NULL) {
		return NULL;
	}

	Queue *toReturn = malloc(sizeof(Queue));

	// Can't assume malloc works every time, no mater how unlikely
	if (toReturn == NULL) {
		return NULL;
	}

	toReturn->front = NULL;
	toReturn->back = NULL;
	toReturn->length = 0;
	toReturn->deleteData = deleteFunc;
	toReturn->printData = printFunc;

	return toReturn;
}


QueueNode *queueNodeNew(void *data) {
	QueueNode *toReturn = malloc(sizeof(QueueNode));

	// Can't assume malloc works every time, no matter how unlikely
	if (toReturn == NULL) {
		return NULL;
	}

	toReturn->data = data;
	toReturn->previous = NULL;
	toReturn->next = NULL;

	return toReturn;
}


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

