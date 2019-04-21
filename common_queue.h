#ifndef __COMMON_QUEUE_H
#define __COMMON_QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct com_queue_node_s {
    struct com_queue_node_s* next;
    void* data;

} com_queue_node_t;

typedef struct {
    com_queue_node_t* head;
    com_queue_node_t* tail;

} com_queue_t;

#define com_queue_empty(x)    ( ((x)->head) ?false :true )
#define com_queue_head(x)    ( (x)->head )

com_queue_t* com_queue_create(void);
void com_queue_destroy(com_queue_t** pp_com_queue);
int com_queue_push(com_queue_t* com_queue, void* data);
void* com_queue_pop(com_queue_t* com_queue);

#endif
