/**
 * @file queue.h
 *
 * @brief General purpose queue implementations.
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * The metadata of a circular FIFO queue with up to 255 max values.
 */
typedef volatile struct QueueFifo {
  uint8_t count;
  uint8_t head;
  uint8_t max;
} QueueFifo;

/**
 * Create a new circular FIFO queue. Drops oldest value in queue on rollover.
 *
 * @return Queue
 */
QueueFifo queue_fifo_new(uint8_t max);

/**
 * Check if queue is empty.
 *
 * @return True if empty
 */
bool queue_fifo_is_empty(QueueFifo *queue);

/**
 * Push onto the queue.
 *
 * @return Tail
 */
uint8_t queue_fifo_push(QueueFifo *queue);

/**
 * Return the current head without modifying the queue.
 *
 * @return Head
 */
uint8_t queue_fifo_peek(QueueFifo *queue);

/**
 * Return the current head and increment.
 *
 * @return Head
 */
uint8_t queue_fifo_pop(QueueFifo *queue);

#endif
