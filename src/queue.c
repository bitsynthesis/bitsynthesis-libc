#include <stdio.h>

#include "queue.h"

QueueFifo queue_fifo_new(uint8_t max) {
  QueueFifo queue = {
    .count = 0,
    .head = 0,
    .max = max
  };
  return queue;
}

bool queue_fifo_is_empty(QueueFifo *queue) {
  return queue->count == 0;
}

uint8_t queue_fifo_push(QueueFifo *queue) {
  uint16_t index = queue->head + queue->count;
  if(queue->max <= index) {
    index = index - queue->max;
  }

  if(queue->count < queue->max) {
    queue->count++;
  } else {
    if(queue->head < queue->max) {
      queue->head++;
    } else {
      queue->head = 0;
    }
  }

  return (uint8_t) index;
}

uint8_t queue_fifo_peek(QueueFifo *queue) {
  return queue->head;
}

uint8_t queue_fifo_pop(QueueFifo *queue) {
  uint8_t index = queue_fifo_peek(queue);
  queue->head++;
  queue->count--;
  return index;
}
