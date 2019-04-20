#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include "process.h"
#include "scheduler.h"
#include <sys/wait.h>

//#include "FIFO.h"
//#include "RR.h"
//#include "SJF.h"
//#include "PSJF.h"

int cmp(const void *a, const void *b){
	struct process *A, *B;
	A = (struct process *)a;
	B = (struct process *)b;
	if(A->t_ready == B->t_ready)
		return A->t_exec - B->t_exec;
	return A->t_ready - B->t_ready;
}

int main(int argc, char *argv[]){
	char sched_policy[256];
	int policy;
	int nproc;
	struct process *proc, *proc_fake;

	scanf("%s", sched_policy);
	scanf("%d", &nproc);

	proc = (struct process *)malloc(nproc *sizeof(struct process));

	for(int i = 0; i < nproc; i++)
		scanf("%s%d%d", proc[i].name, 
			&proc[i].t_ready, &proc[i].t_exec);

	if(strcmp(sched_policy, "FIFO") == 0){
		policy = FIFO;
	}
	else if(strcmp(sched_policy, "RR") == 0){
		policy = RR;
	}
	else if(strcmp(sched_policy, "SJF") == 0){
		policy = SJF;
	}
	else if(strcmp(sched_policy, "PSJF") == 0){
		policy = PSJF;
	}else{
		fprintf(stderr, "Invallid policy: %s", sched_policy);
		exit(0);
	}

	qsort(proc, nproc, sizeof(struct process), cmp);
    for(int i = 0; i < nproc; i++)
		proc[i].task_i = i;
	
	proc_fake = (struct process *)malloc(nproc *sizeof(struct process));
	for(int i = 0; i < nproc; i++)
		proc_fake[i] = proc[i];
	int ntask = scheduling(proc_fake, nproc, policy);

	// TODO: run the sheduled processes.

	// set parent process to parent cpu	
	proc_assign_cpu(getpid(), PARENT_CPU);	
	proc_wakeup(getpid());

	// start
	//unsigned long start_sec, start_nsec, end_sec, end_nsec;
	//syscall(314, &start_sec, &start_nsec);

	char* created = (char*)calloc(nproc, sizeof(char));
	pid_t active_job = 0;
	for (int i = 0; i < ntask; i++){
		int jobID = task_list[i].pid_index;
		struct process *job = &proc[jobID];

		// first block the active job
		if(active_job != 0){
			// check if it's supposed to be finished.
			if (job->t_exec <= 0)
				waitpid(active_job, NULL, 0);
			// if not, block it
			else
				proc_block(active_job);
		}

		// then change the active job
		if(!created[jobID]){
			pid_t ch_pid = proc_exec(*job);
			job->pid = ch_pid;	
			created[jobID] = 1;	
			active_job = ch_pid;
		}else{
			pid_t ch_pid = job->pid;
			proc_wakeup(ch_pid);
			active_job = ch_pid;
		}
		

		// wait for that specific amount of time.
		job->t_exec -= task_list[i].t_exec;
		for(int j = 0; j < task_list[i].t_exec; j++)
			UNIT_T();
	}
	while(wait(NULL)>0);
    //syscall(314, &end_sec, &end_nsec);
    //pid_t ppid = getpid();
    //syscall(333, ppid, start_sec, start_nsec, end_sec, end_nsec);
        
}
