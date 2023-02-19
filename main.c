#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct Foo {
	int a;
	int b;
	int c;
}Foo;

//Driver code to test the generic queue library
int main() {
	queue* q = createQueue(sizeof(Foo));
	if (q == NULL) {
		fprintf(stderr, "Cant create queue\n");
		return -1;
	}

	Foo f;
	f.a = 100;
	f.b = 100;
	f.c = 100;

	if (enqueue(q, &f) == NULL) {
		fprintf(stderr, "Insertion failure\n");
		return -1;
	}
	printf("Enqeued %d\n", f.a);

	Foo frontElem;
	if (front(q, &frontElem) == NULL) {
		fprintf(stderr, "Cant get front element\n");
		return -1;
	}
	printf("Front element of queue is %d\n", frontElem.a);

	for (int i = 0; i < 3; i++) {
		Foo f1;
		f1.c = i + 10;
		f1.b = 0;
		f1.a = 0;
		//Even after f1 goes out of scope we make a copy so it does not matter
		enqueue(q, &f1); //No error checking
		printf("Enqueued %d\n", f1.c); //Showing only one number of the struct for simplicity reasons
	}
	printf("Size of queue is %zd\n", getSize(q));

	printf("Reserving queue\n");
	reverse(q);

	while (!isEmpty(q)) {
		Foo temp;
		//No error checking
		dequeue(q, &temp);
		printf("Dequeued %d\n", temp.c);
	}

	if (clearQueue(q) == NULL) {
		//No error checking
		fprintf(stderr, "Cant clear queue\n");
		return -1;
	}

	printf("Cleared queue\n");
	destroyQueue(&q);
	printf("Destroyed queue\n");

	return 0;
}
