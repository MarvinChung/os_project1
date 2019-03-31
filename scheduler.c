#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
#include "RR.h"
#include "FIFO.h"
#include "SJF.h"
#include "PSJF.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

// Current unit time
static int ntime; 

// Index of running process. -1 if no process running
static int running;

// Number of finish process
static int finish_cnt;

int scheduling(struct process *proc, int nproc, int policy){
    int ntask;
	if(policy == FIFO)
		ntask = FIFO_scheduling_table(proc, nproc);
	if(policy == RR)
		ntask = RR_scheduling_table(proc, nproc);
	if(policy == SJF)
		ntask = SJF_scheduling_table(proc, nproc);
	if(policy == PSJF)
		ntask = PSJF_scheduling_table(proc, nproc);
    
    for(int i = 0; i < nproc; i++)
    	proc[i].pid = -1;

    proc_assign_cpu(getpid(), PARENT_CPU);

    proc_wakeup(getpid());

    ntime = 0;
    running = -1;
    
}
