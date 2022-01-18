# Generic queue

A simple C implementation of a generic queue data structure.
Provides all the basics methods of a queue.

# Basic Usage

```C
include "queue.h"
/*.........*/
typedef struct Foo {
	int a;
}Foo;

Foo f;
f.a =100;
queue* q = createQueue(sizeof(Foo));
enqueue(q, &f);

Foo temp;
dequeue(q, &temp);

destroyQueue(q);
/*..........*/

```

# Example

At main.c there is an example to demonstrate the basic usage of queue.

```bash
make all
./test.out
```
