#include "process_manager.h"
#include <stdio.h>

void initialize_process_manager(PROCESS_MANAGER *pm)
{
    pm->front = 10;
    pm->rear = 9;
    pm->size = 0;
}

bool isFull(PROCESS_MANAGER *pm)
{
    return MAX_PROCESS == pm->size;
}

bool isEmpty(PROCESS_MANAGER *pm)
{
    return pm->size == 0;
}

void insert_front(PROCESS_MANAGER *pm, PROCESS_QUEUE pq)
{
    if (pm->size < MAX_PROCESS)
    {
        pm->front = (pm->front + MAX_PROCESS - 1) % MAX_PROCESS;
        pm->deque[pm->front] = pq;
        pm->size++;
    }
}

void insert_rear(PROCESS_MANAGER *pm, PROCESS_QUEUE pq)
{
    if (pm->size < MAX_PROCESS)
    {
        pm->rear = (pm->rear + 1) % MAX_PROCESS;
        pm->deque[pm->rear] = pq;
        pm->size++;
    }
}

PROCESS_QUEUE delete_front(PROCESS_MANAGER *pm)
{
    if (pm->size > 0)
    {
        PROCESS_QUEUE temp = pm->deque[pm->front];
        pm->front = (pm->front + 1) % MAX_PROCESS;
        pm->size--;
        return temp;
    }
    PROCESS_QUEUE ret_proc_queue_empty;
    initialize_process_queue(&ret_proc_queue_empty);
    return ret_proc_queue_empty;
}

PROCESS_QUEUE delete_rear(PROCESS_MANAGER *pm)
{
    if (pm->size > 0)
    {
        PROCESS_QUEUE temp = pm->deque[pm->rear];
        pm->rear = (pm->rear + MAX_PROCESS - 1) % MAX_PROCESS;
        pm->size--;
        return temp;
    }
    PROCESS_QUEUE ret_proc_queue_empty;
    initialize_process_queue(&ret_proc_queue_empty);
    return ret_proc_queue_empty;
}