# os_project1

1. Assume the struct process ready time is already sorted before passing to the input of schedule functions.
   Therefore main.c should sort the process. 

2. There are 4 functions RR, FIFO, SJF, PSJF to do.\
   There will be 2 parameters pass to these functions, one represents the process structure(include "process.h"), and another is the maximum time that a process can run.\
   The process structure will be sorted by ready time (ascend order). If the ready time is same. It will sorted by the burst time. 
   TODO: Finish the algorithm, then pass the correct process order into the task_list (which will be a global variable).\
   the task_list is an element structure, which will be include inside the "scheduler.h". Return how many numbers you pass into the task_list.
   
