#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Foo
{
  int a;
  int b;
  int c;
} Foo;

void printQueue(queue *q)
{
  printf("\n-----------------\n");
  while(!isEmpty(q))
  {
    Foo temp;
    // No error checking
    dequeue(q, &temp);
    printf("Dequeued %d\n", temp.c);
  }
  printf("-----------------\n");
}

// Driver code to test the generic queue library
int main()
{
  queue *q = createQueue(sizeof(Foo));
  if(q == NULL)
  {
    fprintf(stderr, "Cant create queue\n");
    return -1;
  }

  Foo f;
  f.a = 100;
  f.b = 100;
  f.c = 100;

  // Insert one element into the queue
  if(enqueue(q, &f) == NULL)
  {
    fprintf(stderr, "Insertion failure\n");
    return -1;
  }
  printf("Enqeued %d\n", f.a);

  // Peek the front element
  Foo frontElem;
  if(front(q, &frontElem) == NULL)
  {
    fprintf(stderr, "Cant get front element\n");
    return -1;
  }
  printf("Front element of queue is %d\n", frontElem.a);

  // Insert 3 elements into the queue
  for(int i = 0; i < 3; i++)
  {
    Foo f1;
    f1.c = i + 10;
    f1.b = 0;
    f1.a = 0;
    // Even after f1 goes out of scope we make a copy so it does not matter
    enqueue(q, &f1); // No error checking
    printf(
        "Enqueued %d\n",
        f1.c); // Showing only one number of the struct for simplicity reasons
  }
  printf("Size of queue is %zd\n", getSize(q));

  printf("Reserving queue\n");
  reverse(q);

  queue *deepCopy = copyQueue(q); // No error checking
  printQueue(deepCopy);

  printf("Cleared queue\n");
  destroyQueue(&q);
  destroyQueue(&deepCopy);
  printf("Destroyed queue\n");

  return 0;
}
