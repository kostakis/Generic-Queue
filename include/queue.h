#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h> //For true
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct queue queue;

  /**
   * @param allocSize Size of elements inserted
   * @return queue on success, NULL on error
   */
  queue *createQueue(size_t allocSize);

  /**
   * @param q The queue
   * @param data Data to be inserted
   * @return queue on success, NULL on error
   */
  queue *enqueue(queue *q, void *data);

  /**
   * @param q The queue
   * @param deletedElem The element deleted
   * @return queue on success, NULL on error
   */
  queue *dequeue(queue *q, void *data);

  /**
   * @brief Get the front element
   * @param q The queue
   * @param data The first element
   * @return queue on success, NULL on error
   */
  queue *front(queue *q, void *data);

  /**
   * @brieft Reverse the queue
   * @param The queue
   * @return q, NULL on error
   */
  queue *reverse(queue *q);

  /**
   * @brief Delete all the elements of the queue
   * @param q The queue
   * @return queue on success, NULL on error
   */
  queue *clearQueue(queue *q);

  /**
   * @brief Destroy the queue
   * This will clear, destroy and free all memory of the queue.
   * @param q Pointer to the queue
   */
  void destroyQueue(queue **q);

  /**
   * @param q The queue
   * @return size_t Size of queue, if queue is NULL 0 is returned.
   */
  size_t getSize(queue *q);

  /**
   * @brief Check if queue is empty
   *
   * @param q The queue
   * @return true if size >= 1, false otherwise,
   */
  bool isEmpty(queue *q);

  /**
   * @brief Get the current allocation size that queue uses internally
   *
   * @param q The queue
   * @return allocation size, 0 if queue is NULL
   */
  size_t getAllocationSize(queue *q);

#ifdef __cplusplus
}
#endif

#endif // QUEUE_H
