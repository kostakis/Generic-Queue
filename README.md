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
- Serialization to/from buffers and files

## Building

In both Linux and Windows `compile_commands.json` can be generated to improve intelisense and LSP servers.
```bash
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ln -s build/compile_commands.json compile_commands.json # link/move to the root directory
```


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

## Installation

For linux  

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
cmake .. -DCMAKE_INSTALL_PREFIX=/custom/path
make
make install
```

You can also install on windows using the cmake commands
```bash
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=C:<YOUR_PATH>
cmake --build . --config Release
cmake --install . --config Release
```  
You need to configure then your project or cmake file to link using that location

## Usage Example (with Serialization)

```c
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

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
    Person p3 = {3, "Charlie"};

    enqueue(q, &p1);
    enqueue(q, &p2);
    enqueue(q, &p3);

    printf("Queue size: %zu\n", getSize(q));

    // Demonstrate serialization - save queue to file
    SerializeResult result = serializeQueueToFile(q, "people_queue.dat");
    if (result != SERIALIZE_SUCCESS) {
        fprintf(stderr, "Serialization failed: %d\n", result);
        destroyQueue(&q);
        return 1;
    }
    printf("Queue serialized to file successfully\n");

    // Peek at front element
    Person front_person;
    front(q, &front_person);
    printf("Front: %s (ID: %d)\n", front_person.name, front_person.id);

    // Remove some elements
    Person dequeued;
    dequeue(q, &dequeued);
    printf("Dequeued: %s (ID: %d)\n", dequeued.name, dequeued.id);

    dequeue(q, &dequeued);
    printf("Dequeued: %s (ID: %d)\n", dequeued.name, dequeued.id);

    printf("Queue size after dequeuing: %zu\n", getSize(q));

    // Now demonstrate deserialization - restore queue from file
    destroyQueue(&q);  // Clean up original queue
    
    queue *restored_queue;
    result = deserializeQueueFromFile("people_queue.dat", &restored_queue);
    if (result != SERIALIZE_SUCCESS) {
        fprintf(stderr, "Deserialization failed: %d\n", result);
        return 1;
    }
    printf("Queue deserialized from file successfully\n");
    printf("Restored queue size: %zu\n", getSize(restored_queue));

    // Process all elements from restored queue
    while (!isEmpty(restored_queue)) {
        dequeue(restored_queue, &dequeued);
        printf("Dequeued: %s (ID: %d)\n", dequeued.name, dequeued.id);
    }

    // Clean up
    destroyQueue(&restored_queue);
    remove("people_queue.dat");  // Clean up file
    return 0;
}
```
