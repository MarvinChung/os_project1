// scheduler.h


#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_

#include "process.h"

#define FIFO  1
#define RR    2
#define SJF   3
#define PSJF  4

struct element{
	int pid_index;
	int t_exec;
};

int cmp(const void *a, const void *b);

int next_process(struct process *proc, int nproc, int policy);

int scheduling(struct process *proc, int nproc, int policy);

#endif