// process.c

#define _GNU_SOURCE
#include "process.h"
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include <sys/type.h>
#include <sys/syscall.h>
#define GET_TIME 314
#define PRINTK 315


#define PRINTTIME 333

int proc_assign_cpu(int pid, int core){
	if(core > sizeof(cpu_set_t)){
	    fprintf(stderr, "Core index error.");
        return -1;
	}

	cpu_set_t mask;
	CPU_ZERO(&mask);
    CPU_SET(core, &mask);

    if(sched_setaffinity(pid, sizeof(mask), &mask) < 0){
        perror("sched_seetaffinity");
        exit(1);
    }

    return 0;
}

int proc_exec(struct process proc){
	int pid = fork();

	if(pid < 0){
	    perror("fork");
	    return -1;
	}

	if(pid == 0){
        unsigned long start_sec, start_nsec, end_sec, end_nsec;
        char to_dmesg[256];
        syscall(GET_TIME, &start_sec, &start_nsec);
        for(int i = 0; i < proc.t_exec; i++){
            UNIT_T();
        }
        syscall(GET_TIME, &end_sec, &end_nsec);
        //sprintf(to_dmesg, "[project1] %d %lu.%09lu %lu.%09lu\n",
        //getpid(), start_sec, start_nsec, end_sec, end_nsec);

        //syscall(PRINTK, to_dmesg);
        pid_t ch_pid = getpid();
        syscall(PRINTTIME, ch_pid, start_sec, start_nsec, end_sec, end_nsec);
        exit(0);
	}

	proc_assign_cpu(pid, CHILD_CPU);

	return pid;
}

int proc_block(int pid){
	struct sched_param param;
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);

	if(ret < 0){
	    perror("sched_setscheduler");
	    return -1;
	}

	return ret;
}

int proc_wakeup(int pid){
	struct sched_param param;
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);

	if(ret < 0){
	    perror("sched_setscheduler");
	    return -1;
	}

	return ret;
}
