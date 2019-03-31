# os_project1

1. Processes are sorted in ascending order respect to ready time, if tied, execution time is considered(cmp in main.c).

2. The main function scans the input, sorts processes, decides the correct policy from the input and calls the subroutine scheduling to complete the quest. 

3. There are 4 scheduling policies:round-robin(RR), first in, first out(FIFO), shortest job first(SJF), and preemptive shortest job first(PSJF).\
   There will be at least two parameters for these functions, representing the process structure itself(included in "process.h") and the number of processes. You can freely add additional parameters if needed. 

4. For the function scheduling, it first decides the complete execution configuration(represented by task_list in "scheduler.h") according to the policy and the process structure and then runs processes according to the configuration. \
   TODO: Finish all these four scheduling policies, and pass the correct process order to task_list (which will be a global variable).\
   The task_list is an array of element structures, which is included in "scheduler.h". Return the number of elements( representing switches among processes) passed to the task_list for each scheduling policies. \
   Finish the function scheduling. 
