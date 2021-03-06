#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
//#include "FIFO.h"
#include "Tables.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

#define DEBUG_FIFO
#define DEBUG_RR
#define DEBUG_SJF
#define DEBUG_PSJF
#define RR_TIMESLICE 500

// Current unit time
static int ntime; 

// Index of running process. -1 if no process running
static int running;

// Number of finish process
static int finish_cnt;



int scheduling(struct process *proc, int nproc, int policy){
    int ntask;
#ifdef DEBUG_FIFO
	if(policy == FIFO)
		ntask = FIFO_scheduling_table(proc, nproc);
#endif
#ifdef DEBUG_RR
	if(policy == RR)
		ntask = RR_scheduling_table(proc, nproc, RR_TIMESLICE);
#endif
#ifdef DEBUG_SJF
	if(policy == SJF)
		ntask = SJF_scheduling_table(proc, nproc);
#endif
#ifdef DEBUG_PSJF
	if(policy == PSJF)
		ntask = PSJF_scheduling_table(proc, nproc);
#endif

    for(int i = 0; i < ntask; i++){
	printf("[table info] %s, time: %d \n", proc[task_list[i].pid_index].name
	       , task_list[i].t_exec);
    }
	
//    for(int i = 0; i < nproc; i++)
//    	proc[i].pid = -1;

	
//    proc_assign_cpu(getpid(), PARENT_CPU);

//    proc_wakeup(getpid());

    ntime = 0;
    running = -1;
    
    return ntask;
}
