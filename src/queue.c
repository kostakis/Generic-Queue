#include "queue.h"

#include <string.h>

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
    return NULL;
  }

  toInsert->data = malloc(allocSize);
  if(toInsert->data == NULL)
  {
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
  { // First insertion
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
