# Generic queue

A simple C implementation of a generic queue data structure.
Provides all the basics methods of a queue.

# Supported Operations

* enqueue
* dequeue
* front
* reverse
* getSize
* clearQueue


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

destroyQueue(&q);
/*..........*/

```

See ```main.c``` for a complete example.

# Bulding
## Linux
### Run Example

```bash
cmake -S . -B bin/
cd bin;
make example
./example
```

### Unit Tests

Also have created some basic unit tests using gtest and C++.

```bash
cmake -S . -B bin/
cd bin;
make all
ctest
```

## Windows
```
cmake -S . -B bin/
cd bin;
```
Open the solution file with Visual Studio.
