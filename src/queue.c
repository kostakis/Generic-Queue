#include "queue.h"
#include "SerializeResult.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define QUEUE_MAGIC_NUMBER 0x47515545  // 'GQUE' in ASCII
#define QUEUE_FORMAT_VERSION 1

// Data Structure that will be used when (de)serializing the queue to buffer/files 
typedef struct {
    uint32_t magicNumber;  // Magic number for validation
    uint16_t version;
    uint64_t allocSize;    
    uint64_t count;   
} QueueSerializationHeader;

typedef struct node
{
  void *data;
  struct node *next;
} node;

node *createNode(void *data, size_t allocSize)
{
  node *toInsert = (node *)malloc(sizeof(node));
  if(toInsert == NULL)
  {
    // Malloc allocation failed
    return NULL;
  }

  toInsert->data = malloc(allocSize);
  if(toInsert->data == NULL)
  {
    // Malloc allocation failed - Free the previous allocated node
    free(toInsert);
    return NULL;
  }

  memcpy(toInsert->data, data, allocSize);
  toInsert->next = NULL;

  return toInsert;
}

typedef struct queue
{
  size_t size;
  size_t allocationSize;
  node *head;
  node *tail;
} queue;

queue *createQueue(size_t allocSize)
{
  queue *q = (queue *)malloc(sizeof(queue));
  if(q == NULL)
  {
    return NULL;
  }

  q->allocationSize = allocSize;
  q->size = 0;
  q->head = q->tail = NULL;
  return q;
}

queue *enqueue(queue *q, void *data)
{
  if(q == NULL || data == NULL)
  {
    return NULL;
  }

  node *toInsert = createNode(data, q->allocationSize);
  if(toInsert == NULL)
  {
    return NULL;
  }

  if(q->size == 0)
  {
    // First insertion
    q->head = q->tail = toInsert;
  }
  else
  {
    q->tail->next = toInsert;
    q->tail = toInsert;
  }

  q->size++;

  return q;
}

queue *dequeue(queue *q, void *data)
{
  if(q == NULL)
  {
    return NULL;
  }

  if(q->size == 0)
  {
    return NULL;
  }

  node *toDel = q->head;
  if(q->size == 1)
  {
    memcpy(data, toDel->data, q->allocationSize);
    free(toDel->data);
    free(toDel);
    q->head = q->tail = NULL;
    q->size--;
    return q;
  }

  q->head = q->head->next;
  memcpy(data, toDel->data, q->allocationSize);
  free(toDel->data);
  free(toDel);
  q->size--;

  return q;
}

queue *front(queue *q, void *data)
{
  if(q == NULL)
  {
    return NULL;
  }

  if(q->size == 0)
  {
    return NULL;
  }

  memcpy(data, q->head->data, q->allocationSize);

  return q;
}

queue *reverse(queue *q)
{
  if(q == NULL)
    return NULL;
  if(q->size == 0)
    return q; // Nonthing to reverse
  else
  {
    void *data = malloc(q->allocationSize);
    if(data != NULL)
    {
      dequeue(q, data);
      reverse(q);
      enqueue(q, data);
      free(data);
    }
    return q;
  }
}

queue *clearQueue(queue *q)
{
  if(q == NULL)
  {
    return NULL;
  }

  while(!isEmpty(q))
  {
    node *temp = q->head;
    q->head = q->head->next;
    free(temp->data);
    free(temp);
    q->size--;
  }

  return q;
}

size_t getSize(queue *q)
{
  if(q == NULL)
  {
    return 0;
  }

  return q->size;
}

bool isEmpty(queue *q)
{
  return q->size == 0 ? true : false;
}

size_t getAllocationSize(queue *q)
{
  if(q == NULL)
  {
    return 0;
  }

  return q->allocationSize;
}

queue *copyQueue(queue *src)
{
  if(src == NULL)
  {
    return NULL;
  }

  queue *newQueue = createQueue(src->allocationSize);
  if(newQueue == NULL)
  {
    return NULL;
  }

  // Iterate through original queue and copy nodes
  node *currentOriginalNode = src->head;
  node *previousNewNode = NULL;
  while(currentOriginalNode != NULL)
  {
    enqueue(newQueue, currentOriginalNode->data);
    currentOriginalNode = currentOriginalNode->next;
  }

  return newQueue;
}

void destroyQueue(queue **q)
{
  if(q == NULL)
  {
    return;
  }

  clearQueue(*q);
  free(*q);
  *q = NULL;
}

void *find(queue *q, bool (*predicate)(void *data))
{
  if(q == NULL || q->size == 0)
  {
    return NULL;
  }

  if(predicate == NULL)
  {
    return NULL;
  }

  node *current = q->head;

  while(current != NULL)
  {
    if(predicate(current->data))
    {
      return current->data;
    }

    current = current->next;
  }

  return NULL;
}

void *findMem(queue *q, const void *data)
{
  if(q == NULL || data == NULL)
  {
    return NULL;
  }

  if(q->size == 0)
  {
    return NULL;
  }

  node *current = q->head;
  while(current != NULL)
  {
    if(memcmp(current->data, data, q->allocationSize) == 0)
    {
      return current->data;
    }
    current = current->next;
  }

  return NULL;
}

SerializeResult serializeQueueToBuffer(queue *q, void *buffer, size_t bufferSize)
{
    // NULL CHECKS
    if (q == NULL || buffer == NULL) {
        return SERIALIZE_ERROR_NULL_POINTER;
    }

    size_t queueSize = getSize(q);
    if (queueSize == 0) {
        return SERIALIZE_ERROR_EMPTY_QUEUE;
    }

    size_t headerSize = sizeof(QueueSerializationHeader);
    size_t allDataSize = queueSize * q->allocationSize;
    size_t wholeBufferSize = headerSize + allDataSize;

    if (bufferSize < wholeBufferSize) {
        return SERIALIZE_ERROR_SIZE_MISMATCH;
    }

    QueueSerializationHeader *header = (QueueSerializationHeader*) buffer;
    header->allocSize = (uint64_t)q->allocationSize;
    header->count = (uint64_t)queueSize;
    header->version = QUEUE_FORMAT_VERSION;
    header->magicNumber = QUEUE_MAGIC_NUMBER;

    // Copy data after the header
    uint8_t *dataStart = (uint8_t*)buffer + headerSize;
    size_t index = 0;
    node* current = q->head;
   
    while(current != NULL && index < queueSize)
    {
        memcpy(dataStart + (index * q->allocationSize), current->data, q->allocationSize);
        current = current->next;
        index++;
    }

    return SERIALIZE_SUCCESS;
}

SerializeResult serializeQueueToNewBuffer(queue *q, void **buffer, size_t *bufferSize)
{
    if (q == NULL || buffer == NULL || bufferSize == NULL) {
        return SERIALIZE_ERROR_NULL_POINTER;
    }

    size_t queueSize = getSize(q);
    if(queueSize == 0)
    {
        return SERIALIZE_ERROR_EMPTY_QUEUE;
    }

    size_t headerSize = sizeof(QueueSerializationHeader);
    size_t allDataSize = queueSize * q->allocationSize;
    size_t wholeBufferSize = headerSize + allDataSize;
    *bufferSize = wholeBufferSize;

    *buffer = malloc(wholeBufferSize);
    if (*buffer == NULL) {
        return SERIALIZE_ERROR_ALLOCATION_FAILED;
    }

    return serializeQueueToBuffer(q, *buffer, wholeBufferSize);
}

SerializeResult deserializeQueueFromBuffer(void *buffer, size_t bufferSize, queue **result) {
    // Input validation
    if (buffer == NULL || result == NULL) {
        return SERIALIZE_ERROR_NULL_POINTER;
    }
    
    *result = NULL;
    
    // Check minimum buffer size for header
    size_t headerSize = sizeof(QueueSerializationHeader);
    if (bufferSize < headerSize) {
        return SERIALIZE_ERROR_INVALID_HEADER;
    }
    
    // Read and validate header
    QueueSerializationHeader *header = (QueueSerializationHeader*)buffer;
    if (header->magicNumber != QUEUE_MAGIC_NUMBER) {
        return SERIALIZE_ERROR_INVALID_HEADER;
    }
    
    if (header->version != QUEUE_FORMAT_VERSION) {
        return SERIALIZE_ERROR_VERSION_MISMATCH;
    }
    
    // Create new queue
    *result = createQueue((size_t)header->allocSize);
    if (*result == NULL) {
        return SERIALIZE_ERROR_ALLOCATION_FAILED;
    }
    
    // Check if buffer contains enough data
    size_t expectedDataSize = headerSize + (header->count * header->allocSize);
    if (bufferSize < expectedDataSize) {
        destroyQueue(result);
        return SERIALIZE_ERROR_CORRUPTED_DATA;
    }
    
    // Deserialize elements
    uint8_t *dataPtr = (uint8_t*)buffer + headerSize;
    for (uint64_t i = 0; i < header->count; i++) {
        if (enqueue(*result, dataPtr + (i * header->allocSize)) == NULL) {
            destroyQueue(result);
            return SERIALIZE_ERROR_ALLOCATION_FAILED;
        }
    }
    
    return SERIALIZE_SUCCESS;
}

SerializeResult serializeQueueToFile(queue *q, const char *filename) {
    // Input validation
    if (q == NULL || filename == NULL) {
        return SERIALIZE_ERROR_NULL_POINTER;
    }
    
    if (q->size == 0) {
        return SERIALIZE_ERROR_EMPTY_QUEUE;
    }
    
    // Allocate buffer for serialization
    void *buffer = NULL;
    size_t bufferSize = 0;
    SerializeResult result = serializeQueueToNewBuffer(q, &buffer, &bufferSize);
    
    if (result != SERIALIZE_SUCCESS) {
        return result;
    }
    
    // Write to file
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        free(buffer);
        return SERIALIZE_ERROR_IO_FAILURE;
    }
    
    size_t written = fwrite(buffer, 1, bufferSize, file);
    fclose(file);
    free(buffer);
    
    if (written != bufferSize) {
        return SERIALIZE_ERROR_IO_FAILURE;
    }
    
    return SERIALIZE_SUCCESS;
}

SerializeResult deserializeQueueFromFile(const char *filename, queue **result) {
    // Input validation
    if (filename == NULL || result == NULL) {
        return SERIALIZE_ERROR_NULL_POINTER;
    }
    
    *result = NULL;
    
    // Open file
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return SERIALIZE_ERROR_IO_FAILURE;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (fileSize <= 0) {
        fclose(file);
        return SERIALIZE_ERROR_CORRUPTED_DATA;
    }
    
    // Allocate buffer
    void *buffer = malloc(fileSize);
    if (buffer == NULL) {
        fclose(file);
        return SERIALIZE_ERROR_ALLOCATION_FAILED;
    }
    
    // Read file
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    fclose(file);
    
    if (bytesRead != (size_t)fileSize) {
        free(buffer);
        return SERIALIZE_ERROR_IO_FAILURE;
    }
    
    // Deserialize
    SerializeResult serResult = deserializeQueueFromBuffer(buffer, bytesRead, result);
    free(buffer);
    
    return serResult;
}
