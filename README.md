# Generic Queue

A lightweight generic queue implementation in C. This library provides a complete FIFO (First-In-First-Out) queue data structure that works with any data type through `void*` pointer.

**Library:** Pure C
**Tests:** C++ with Google Test

## Features

- Generic implementation supporting any data type
- Deep copy semantics for safe memory management
- Search functionality with custom predicates or memory comparison
- Queue reversal and copy operations
- Comprehensive error handling
- Zero dependencies for library users

## Building

### Linux

```bash
mkdir build && cd build
cmake ..
make
```

### Windows

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

On Windows, executables and libraries will be in the `Debug/` or `Release/` folder. You can also open the generated `.sln` file in Visual Studio.

## Running Examples

### Linux
```bash
./example
```

### Windows
```bash
Debug\example.exe
```

## Running Tests

The library includes comprehensive unit tests written in C++ using Google Test.

### Linux
```bash
cd build
ctest
# Or run the test executable
./tests/QueueTest
# Or run the test target (after make all)
make test
```

### Windows
```bash
cd build
ctest
# or 
Debug\QueueTest.exe
```

## Installation (Linux)

```bash
mkdir build && cd build
cmake ..
make
sudo make install
```

This installs:
- `libgenericQueue.a` to `/usr/local/lib`
- `queue.h` to `/usr/local/include`

To install to a custom location:
```bash
cmake -DCMAKE_INSTALL_PREFIX=/custom/path ..
make
make install
```

## API

- `queue *createQueue(size_t allocSize)` - Create a new queue
- `void destroyQueue(queue **q)` - Destroy queue and free memory
- `queue *enqueue(queue *q, void *data)` - Add element to back
- `queue *dequeue(queue *q, void *data)` - Remove and retrieve front element
- `queue *front(queue *q, void *data)` - Peek at front element
- `queue *reverse(queue *q)` - Reverse the queue order
- `queue *clearQueue(queue *q)` - Remove all elements
- `queue *copyQueue(queue *src)` - Create a deep copy
- `void *find(queue *q, bool (*predicate)(void *data))` - Find element with predicate
- `void *findMem(queue *q, void *data)` - Find element by memory comparison
- `size_t getSize(queue *q)` - Get number of elements
- `bool isEmpty(queue *q)` - Check if queue is empty
- `size_t getAllocationSize(queue *q)` - Get element size

See `queue.h` for detailed documentation.

## Usage Example

```c
#include "queue.h"
#include <stdio.h>

typedef struct {
    int id;
    char name[32];
} Person;

int main() {
    // Create queue for Person structs
    queue *q = createQueue(sizeof(Person));
    if (q == NULL) {
        fprintf(stderr, "Failed to create queue\n");
        return 1;
    }

    // Add elements
    Person p1 = {1, "Alice"};
    Person p2 = {2, "Bob"};

    enqueue(q, &p1);
    enqueue(q, &p2);

    printf("Queue size: %zu\n", getSize(q));

    // Peek at front
    Person front_person;
    front(q, &front_person);
    printf("Front: %s\n", front_person.name);

    // Remove elements
    Person dequeued;
    while (!isEmpty(q)) {
        dequeue(q, &dequeued);
        printf("Dequeued: %s\n", dequeued.name);
    }

    // Clean up
    destroyQueue(&q);
    return 0;
}
```
