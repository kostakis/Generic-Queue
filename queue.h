#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _data {
	void * data;
	struct _data * next;
}data;

typedef struct _queue {
	size_t size;
	size_t allocationSize;
	data* head;
	data* tail;
}queue;
/*
Create and return an empty queue
*/
queue* createQueue(size_t allocSize);
/*
Insert data into the queue(last position)
*/
void enqueue(queue * q, void* data);
/*
Remove first element of the queue of save its value to the toRet argument
*/
void  dequeue(queue * q, void * toRet);
/*
Save first element of the queue to the toRet argument
*/
void front(queue*q, void *toRet);//Return the first element
/*
Deletes all data of the queue
*/
void clearQueue(queue* q);
/*
Clears and destoys the queue
*/
void destroyQueue(queue *q);
/*
Return size of the queue
*/
size_t getSize(queue *q);
/*
Check is queue is empty
*/
bool isEmpty(queue * q);


#endif
