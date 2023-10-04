# Generic queue

A simple C implementation of a generic queue data structure.
Provides all the basics methods of a queue.
It can be used as a static library  

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
cmake -S . -B build/
cd build;
make example
./example
```
  
You can also run ```make genericQueue``` to build just the library

### Unit Tests

Also have created some basic unit tests using gtest and C++.  
Test are compiled automatically but you must run them.

```bash
cmake -S . -B build/
cd build;
make all # This also compiles and executes the unit tests
ctest
```

## Windows
```bash
cmake -S . -B build/
cd build;
cmake --build .
ctest # To run the tests
```

In the Debug/ folder the example is located together with the static library.    

You can also open the solution file with visual studio.
