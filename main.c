// main.c

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include "process.h"
#include "scheduler.h"

int main(int argc, char *argv[]){
	char sched_policy[256];
	int policy;
	int nproc;
	struct process *proc;

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
	scheduling(proc, nproc, policy);
}