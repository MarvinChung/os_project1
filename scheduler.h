// scheduler.h

#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_

#define FIFO  1
#define RR    2
#define SJF   3
#define PSJF  4
#define MAXLENGTH 0xffff

struct element{
	int pid_index;
	int t_exec;
};

struct element task_list[MAXLENGTH];

int scheduling(struct process *proc, int nproc, int policy);

#endif
