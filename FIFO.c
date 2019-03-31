#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

int FIFO_scheduling_table(struct process *proc, int nproc){
    for(int i = 0; i < nproc; i++){
        task_list[i].pid_index = i;
        task_list[i].t_exec = proc[i].t_exec;
    }
    return nproc;
}