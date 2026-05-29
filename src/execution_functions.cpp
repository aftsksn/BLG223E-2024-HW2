#include "execution_functions.h"
#include <iostream>
using namespace std;

void read_process_file(const char *filename, PROCESS_MANAGER *pm)
{
    FILE* file = fopen(filename, "r");
    if (!file) return; 

    initialize_process_manager(pm);
    PROCESS_QUEUE current_queue;
    initialize_process_queue(&current_queue);
    PROCESS process;
    
    char header[100];
    fgets(header, sizeof(header), file); //ilk satır salağı için
    int pid, priority, isHead;
    while (fscanf(file, "%d, %d, %d", &pid, &priority, &isHead) == 3) {
        initialize_process(&process, pid, priority);
        if (isHead == 1) 
        {
            enqueue(&current_queue, process);
            current_queue.priority = priority;
            if (current_queue.priority == 1) 
            {
                insert_front(pm, current_queue);
            } else 
            {
                insert_rear(pm, current_queue);
            }
            initialize_process_queue(&current_queue);
            continue;
        }
        enqueue(&current_queue, process);
    }
    fclose(file);
}

void read_insertion_file(const char *filename, INSERTION_QUEUE *eq)
{
    FILE *file = fopen(filename, "r");
    if (!file) return;
    
    initialize_execution_queue(eq);
    PROCESS_QUEUE current_queue;
    initialize_process_queue(&current_queue);
    PROCESS process;

    char header[100];
    fgets(header, sizeof(header), file);
    int iteration, pid, priority, isHead;
    while (fscanf(file, "%d, %d, %d, %d", &iteration, &pid, &priority, &isHead) == 4) {
        initialize_process(&process, pid, priority);
        if (isHead == 1) 
        {
            enqueue(&current_queue, process);
            current_queue.priority = priority;
            current_queue.iteration = iteration;
            enqueue(eq, current_queue);
            initialize_process_queue(&current_queue);
            continue;
        }
        enqueue(&current_queue, process);
    }
    fclose(file);
}

void execution_loop(PROCESS_MANAGER *pm, INSERTION_QUEUE *eq, FAILURE_STACK *fs)
{
    int iteration = 0;
    initialize_failed_stack(fs);
    // Open the output file for writing
    FILE *outputFile = fopen("execution_run.txt", "w");
    if (!outputFile) return;

    while (!isEmpty(pm)) {
        PROCESS_QUEUE current_queue = delete_front(pm);
        for (int i = current_queue.front; i <= current_queue.rear; i++)
        {
            printf("Iteration %d:\n", iteration);
            PROCESS process = peek(&current_queue);
            if(process.pid % 8 == 0)
            {
                fprintf(outputFile, "%d, %s\n", process.pid, "f");
                push (fs, current_queue);
                break;
            }
            fprintf(outputFile, "%d, %s\n", process.pid, "s");
            dequeue(&current_queue);

            // arriving processlere bak
            PROCESS_QUEUE current_queue2 = peek(eq); 
            if (current_queue2.iteration == iteration) {
                if (current_queue2.priority == 1) 
                {
                    insert_front(pm, current_queue2);
                }
                if (current_queue2.priority == 0) 
                {
                    insert_rear(pm, current_queue2);
                }
                dequeue(eq); 
            }
            iteration++;
        }    
    }
    fclose(outputFile);
}