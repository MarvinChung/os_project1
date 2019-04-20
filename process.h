// process.h
#pragma once
#ifndef _PROCESS_H_
#define _PROCESS_H_

// #include<sys/type.h>

#define CHILD_CPU 1
#define PARENT_CPU 0


#define UNIT_T()                    \
{                                   \
	volatile unsigned long i;       \
	for(i = 0; i< 1000000UL; i++);  \
}                                   \


struct process{
    char name[32];
    int t_ready, t_exec, task_i;
//    pid_t pid;	
};


int proc_assign_cpu(int pid, int core);

int proc_exec(struct process proc);

int proc_block(int pid);

int proc_wakeup(int pid);


#endif