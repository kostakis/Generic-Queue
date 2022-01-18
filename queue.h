#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _data {
	void* data;
	struct _data* next;
}data;

typedef struct _queue {
	size_t size;
	size_t allocationSize;
	data* head;
	data* tail;
}queue;

/**
 * @param allocSize Size of elements insrted
 * @return queue object
 */
queue* createQueue(size_t allocSize);

/**
 * @param q The queue
 * @param data Data to be inserted
 */
void enqueue(queue* q, void* data);

/**
 * @param q The queue
 * @param deletedElem The element deleted
 */
void dequeue(queue* q, void* toRet);

/**
 * @brief Get the front element
 * @param q The queue
 * @param toRet The first element
 */
void front(queue* q, void* toRet);

/**
 * @brief Delete all the elements of the queue
 * 
 * @param q The queue
 */
void clearQueue(queue* q);

/**
 * @brief Destroy the queue
 * 
 * @param q The queue
 */
void destroyQueue(queue* q);

/**
 * @param q The queue
 * @return size_t Size of queue
 */
size_t getSize(queue* q);

/**
 * @brief Check if queue is empty
 * 
 * @param q The queue
 * @return true if size >= 1, false otherwise
 */
bool isEmpty(queue* q);

#endif
