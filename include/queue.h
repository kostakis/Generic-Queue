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
   * @brief Removes and saves into the data parameter the
   * first element (head) of the queue. Decreases size by 1.
   * @param q The queue
   * @param deletedElem Where to save the deleted element
   * @return queue on success, NULL on error
   */
  queue *dequeue(queue *q, void *data);

  /**
   * @brief Get the front element
   * @param q The queue
   * @param data Variable to save the data
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

  /**
   * @brief Creates a deep copy of the queue
   *
   * @param src The queue to be copied
   * @return The new queue, NULL on error
   */
  queue *copyQueue(queue *src);

  /**
   * @brief Find the first element that matches the predicate using predicate
   *
   * @param q The queue
   * @param predicate Function that returns true for matching element
   * @return Pointer to the found element's data, NULL if not found or on error
   */
  void *find(queue *q, bool (*predicate)(void *data));

  /**
   * @brief Find an element in the queue by doing memory comporasion using memcmp
   *
   * @param q The queue
   * @param data The data to search for
   * @return Pointer to the found element's data, NULL if not found or on error
   */
  void *findMem(queue *q, void *data);

#ifdef __cplusplus
}
#endif

#endif // QUEUE_H
