#pragma once
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct temp {
	int a;
	int b;
	int c;
};

int main() {
	queue* q = createQueue(sizeof(struct temp));
	for (int i = 0; i < 10; i++) {
		struct temp a; 
		a.c = i+10;
		a.b = 0;
		a.a = 0;
		enqueue(q, &a);
	}
	printf("Size of queue is %ld\n",getSize(q));
	while (!isEmpty(q)) {
		struct temp temp;
		dequeue(q, &temp);
		printf("Dequeued %d\n",temp.c);
	}
	clearQueue(q);
	printf("Cleared queue\n");
	printf("Size of queue is %ld\n",getSize(q));
	destroyQueue(q);
	printf("Destroyed queue\n");
	return 0;
}
