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

queue* createQueue(size_t allocSize);
void enqueue(queue * q, void* data);//Create and return an empty queue
void  dequeue(queue * q, void * toRet);//Delete first element and save its value to second argument
void * front(queue*q);//Return the first element
void clearQueue(queue* q);//Deletes each element of the queue
void destroyQueue(queue *q);//Destroys and clears the whole queue
size_t getSize(queue *q);
bool isEmpty(queue * q);


#endif
