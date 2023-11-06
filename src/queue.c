#include "queue.h"

#include <string.h>

typedef struct node {
  void *data;
  struct node *next;
} node;

typedef struct queue {
  size_t size;
  size_t allocationSize;
  node *head;
  node *tail;
} queue;

queue *createQueue(size_t allocSize) {
  queue *q = (queue *)malloc(sizeof(queue));
  if (q == NULL)
    return NULL;

  q->allocationSize = allocSize;
  q->size = 0;
  q->head = q->tail = NULL;
  return q;
}

queue *enqueue(queue *q, void *data) {
  if (q == NULL)
    return NULL;

  node *toInsert = (node *)malloc(sizeof(node));
  if (toInsert == NULL)
    return NULL;

  toInsert->data = malloc(q->allocationSize);
  if (toInsert->data == NULL) {
    free(toInsert);
    return NULL;
  }

  toInsert->next = NULL;
  memcpy(toInsert->data, data, q->allocationSize);

  if (q->size == 0) { // First insertion
    q->head = q->tail = toInsert;
  } else {
    q->tail->next = toInsert;
    q->tail = toInsert;
  }

  q->size++;

  return q;
}

queue *dequeue(queue *q, void *data) {
  if (q == NULL)
    return NULL;
  if (q->size == 0)
    return NULL;

  node *toDel = q->head;
  if (q->size == 1) {
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

queue *front(queue *q, void *data) {
  if (q == NULL)
    return NULL;

  if (q->size == 0)
    return NULL;

  memcpy(data, q->head->data, q->allocationSize);

  return q;
}

queue *reverse(queue *q) {
  if (q == NULL)
    return NULL;
  if (q->size == 0)
    return q; // Nonthing to reverse
  else {
    void *data = malloc(q->allocationSize);
    if (data != NULL) {
      dequeue(q, data);
      reverse(q);
      enqueue(q, data);
      free(data);
    }
    return q;
  }
}

queue *clearQueue(queue *q) {
  if (q == NULL)
    return NULL;

  while (!isEmpty(q)) {
    node *temp = q->head;
    q->head = q->head->next;
    free(temp->data);
    free(temp);
    q->size--;
  }

  return q;
}

size_t getSize(queue *q) {
  if (q == NULL)
    return 0;
  return q->size;
}

bool isEmpty(queue *q) { return q->size == 0 ? true : false; }

size_t getAllocationSize(queue *q) {
  if (q == NULL)
    return 0;

  return q->allocationSize;
}

void destroyQueue(queue **q) {
  clearQueue(*q);
  free(*q);
  *q = NULL;
}
