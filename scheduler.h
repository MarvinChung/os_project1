// scheduler.h


#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_

#include "process.h"

#define FIFO  1
#define RR    2
#define SJF   3
#define PSJF  4
#define MAXLENGTH 0xffffffffffffffff

struct element{
	int pid_index;
	int t_exec;
};

struct element task_list[MAXLENGTH];

int FIFO_scheduling_table(struct process *proc, int nproc);
int RR_scheduling_table(struct process *proc, int nproc);
int SJF_scheduling_table(struct process *proc, int nproc);
int PSJF_scheduling_table(struct process *proc, int nproc);

int scheduling(struct process *proc, int nproc, int policy);

#endif
