#define _GNU_SOURCE
//#include "FIFO.h"
#include "Tables.h"
int FIFO_scheduling_table(struct process *proc, int nproc){
    for(int i = 0; i < nproc; i++){
        task_list[i].pid_index = i;
        task_list[i].t_exec = proc[i].t_exec;
    }
    return nproc;
}