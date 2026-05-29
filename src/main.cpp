#include "type_process.h"
#include "process_queue.h"
#include "process_manager.h"
#include "execution_functions.h"
#include <stdio.h>

int main()
{
    PROCESS_MANAGER pm;
    initialize_process_manager(&pm);
    INSERTION_QUEUE iq;
    initialize_execution_queue(&iq);
    FAILURE_STACK fs;
    initialize_failed_stack(&fs);
    read_process_file("initial_processes.txt", &pm);
    read_insertion_file("arriving_processes.txt", &iq);
    execution_loop(&pm, &iq, &fs);
    return 0;
}