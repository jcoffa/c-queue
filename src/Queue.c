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
	toReturn->next = NULL;

	return toReturn;
}


void queueClear(Queue *queue) {
	if (queue == NULL) {
		return;
	}

	void *toFree;
	while ((toFree = dequeue(queue)) != NULL) {
		// dequeue already frees the QueueNode,
		// so we only have to free the data it held
		queue->deleteData(toFree);
	}
}


void queueFree(Queue *queue) {
	if (queue == NULL) {
		return;
	}

	queueClear(queue);
	free(queue);
}


bool enqueue(Queue *queue, void *data) {
	if (queue == NULL) {
		return false;
	}

	QueueNode *toEnqueue = queueNodeNew(data);

	// Can't assume malloc works every time, no matter how unlikely
	if (toEnqueue == NULL) {
		return false;
	}

	// Enqueueing a node is slightly different if the queue is empty
	if (queueIsEmpty(queue)) {
		// When a queue is empty, its front node is also its back node
		queue->front = toEnqueue;
	} else {
		// Add the new node to the back of the queue
		queue->back->next = toEnqueue;
	}
	
	queue->back = toEnqueue;
	(queue->length)++;
	return true;
}


void *dequeue(Queue *queue) {
	if (queue == NULL || queueIsEmpty(queue)) {
		return NULL;
	}

	QueueNode *front = queue->front;
	void *toReturn = front->data;

	// Update the pointers in the queue and its front node
	if (queue->front == queue->back) {
		// There was 1 node in the queue, and now there are 0
		queue->front = NULL;
		queue->back = NULL;
	} else {
		// There was 2 or more nodes in the queue
		queue->front = queue->front->next;
	}

	free(front);
	(queue->length)--;

	return toReturn;
}


void *queuePeekFront(const Queue *queue) {
	if (queue == NULL || queueIsEmpty(queue)) {
		return NULL;
	}

	return queue->front->data;
}


void *queuePeekBack(const Queue *queue) {
	if (queue == NULL || queueIsEmpty(queue)) {
		return NULL;
	}

	return queue->back->data;
}


unsigned int queueGetLength(const Queue *queue) {
	if (queue == NULL) {
		return 0;
	}

	return queue->length;
}


bool queueIsEmpty(const Queue *queue) {
	return queueGetLength(queue) == 0;
}


char *queueFrontToString(const Queue *queue) {
	if (queue == NULL) {
		return NULL;
	}

	char *toReturn;
	if (queueIsEmpty(queue)) {
		toReturn = malloc(sizeof(char));
		toReturn[0] = '\0';
	} else {
		toReturn = queue->printData(queue->front->data);
	}

	return toReturn;
}


char *queueBackToString(const Queue *queue) {
	if (queue == NULL) {
		return NULL;
	}

	char *toReturn;
	if (queueIsEmpty(queue)) {
		toReturn = malloc(sizeof(char));
		toReturn[0] = '\0';
	} else {
		toReturn = queue->printData(queue->back->data);
	}

	return toReturn;
}


void queuePrintFront(const Queue *queue) {
	char *toPrint = queueFrontToString(queue);
	if (toPrint != NULL) {
		printf("%s\n", toPrint);
		free(toPrint);
	}
}


void queuePrintBack(const Queue *queue) {
	char *toPrint = queueBackToString(queue);
	if (toPrint != NULL) {
		printf("%s\n", toPrint);
		free(toPrint);
	}
}


char *queueToString(const Queue *queue) {
	if (queue == NULL) {
		return NULL;
	}

	// Start with the front of the queue
	char *toReturn = queueFrontToString(queue);
	size_t length = strlen(toReturn);

	// Prepare to iterate over the rest of the queue beyond the front
	QueueNode *cur;
	if (queueIsEmpty(queue)) {
		// If the queue is empty then `cur = queue->front->next`
		// will error out or segfault since `queue->front` is NULL,
		// so this guard is necessary
		cur = NULL;
	} else {
		cur = queue->front->next;
	}

	while (cur != NULL) {
		char *nodeStr = queue->printData(cur->data);
		length += strlen(nodeStr) + 1;	// +1 for newline
		toReturn = realloc(toReturn, length + 1);	// +1 for null terminator
		strcat(toReturn, "\n");
		strcat(toReturn, nodeStr);
		free(nodeStr);

		cur = cur->next;
	}

	return toReturn;
}


void queuePrint(const Queue *queue) {
	char *toPrint = queueToString(queue);
	if (toPrint != NULL) {
		printf("%s\n", toPrint);
		free(toPrint);
	}
}


void queueMapNodes(Queue *queue, void (*func)(QueueNode *)) {
	if (queue == NULL) {
		return;
	}

	QueueNode *cur = queue->front;
	while (cur != NULL) {
		func(cur);
	}
}


void queueMapData(Queue *queue, void (*func)(void *)) {
	if (queue == NULL) {
		return;
	}

	QueueNode *cur = queue->front;
	while (cur != NULL) {
		func(cur->data);
	}
}

