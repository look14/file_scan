#include "common_queue.h"

com_queue_t* com_queue_create(void)
{
	com_queue_t* com_queue = (com_queue_t*)calloc(sizeof(com_queue_t), 1);

	if(NULL == com_queue)
		return NULL;

	return com_queue;
}

void com_queue_destroy(com_queue_t** pp_com_queue)
{
	com_queue_t* com_queue = (pp_com_queue) ?(*pp_com_queue) :NULL;

	if(NULL == com_queue)
		return;

	free(com_queue);
	*pp_com_queue = NULL;
}

int com_queue_push(com_queue_t* com_queue, void* data)
{
	com_queue_node_t* tmp = (com_queue_node_t*)calloc(sizeof(com_queue_node_t), 1);

	if(NULL == tmp)
		return -1;

	tmp->data = data;

	if(NULL == com_queue->head)
		com_queue->head = tmp;
	else
		com_queue->tail->next = tmp;

	com_queue->tail = tmp;

	return 0;
}

void* com_queue_pop(com_queue_t* com_queue)
{
	com_queue_node_t* tmp;
	void* data;

	if(NULL == com_queue->head)
		return NULL;

	tmp = com_queue->head;
	data = tmp->data;

	com_queue->head = com_queue->head->next;

	if(NULL == com_queue->head)
		com_queue->tail = NULL;

	free(tmp);

	return data;
}
