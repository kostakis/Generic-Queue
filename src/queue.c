#include "queue.h"

#include <string.h>

typedef struct _data {
  void *data;
  struct _data *next;
} data;

typedef struct queue {
  size_t size;
  size_t allocationSize;
  data *head;
  data *tail;
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

queue *enqueue(queue *q, void *_data) {
  if (q == NULL)
    return NULL;

  data *toInsert = (data *)malloc(sizeof(data));
  if (toInsert == NULL)
    return NULL;

  toInsert->data = malloc(q->allocationSize);
  if (toInsert->data == NULL)
    return NULL;

  toInsert->next = NULL;
  memcpy(toInsert->data, _data, q->allocationSize);

  if (q->size == 0) { // First insertion
    q->head = q->tail = toInsert;
  } else {
    q->tail->next = toInsert;
    q->tail = toInsert;
  }

  q->size++;

  return q;
}

queue *dequeue(queue *q, void *toRet) {
  if (q == NULL)
    return NULL;
  if (q->size == 0)
    return NULL;

  data *toDel = q->head;
  if (q->size == 1) {
    memcpy(toRet, toDel->data, q->allocationSize);
    free(toDel->data);
    free(toDel);
    q->head = q->tail = NULL;
    q->size--;
    return q;
  }

  q->head = q->head->next;
  memcpy(toRet, toDel->data, q->allocationSize);
  free(toDel->data);
  free(toDel);
  q->size--;

  return q;
}

queue *front(queue *q, void *toRet) {
  if (q == NULL)
    return NULL;

  if (q->size == 0)
    return NULL;

  memcpy(toRet, q->head->data, q->allocationSize);

  return q;
}

queue *reverse(queue *q) {
  if (q == NULL)
    return NULL;
  if (q->size == 0)
    return q; // Nonthing to reserve
  else {
    data temp;
    dequeue(q, &temp);
    reverse(q);
    enqueue(q, &temp);
    return q;
  }
}

queue *clearQueue(queue *q) {
  if (q == NULL)
    return NULL;

  while (!isEmpty(q)) {
    data *temp = q->head;
    q->head = q->head->next;
    free(temp->data);
    free(temp);
    q->size--;
  }

  return q;
}

size_t getSize(queue *q) { return q->size; }

bool isEmpty(queue *q) { return q->size == 0 ? true : false; }

void destroyQueue(queue **q) {
  clearQueue(*q);
  free(*q);
  *q = NULL;
}
