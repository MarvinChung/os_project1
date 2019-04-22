// process.c

#define _GNU_SOURCE
#include "process.h"
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/syscall.h>
#define GET_TIME 96
#define PRINTK 315


#define PRINTTIME 333

int proc_assign_cpu(pid_t pid, int core){
	if(core > sizeof(cpu_set_t)){
	    fprintf(stderr, "Core index error.");
        return -1;
	}

	cpu_set_t mask;
	CPU_ZERO(&mask);
    CPU_SET(core, &mask);

    if(sched_setaffinity(pid, sizeof(mask), &mask) < 0){
        perror("sched_setaffinity");
        exit(1);
    }

    return 0;
}

pid_t proc_exec(struct process proc){
	pid_t pid = fork();

	if(pid < 0){
	    perror("fork");
	    return -1;
	}

	if(pid == 0){
        //unsigned long start_sec, start_nsec, end_sec, end_nsec;
        struct timeval start_tv, end_tv;
        pid_t ch_pid = getpid();
        proc_assign_cpu(ch_pid, CHILD_CPU);
        
        syscall(GET_TIME, &start_tv, NULL);
        for(int i = 0; i < proc.t_exec; i++){
            UNIT_T();
        }
        syscall(GET_TIME, &end_tv, NULL);
        
        syscall(PRINTTIME, ch_pid, start_tv.tv_sec, 1000 * start_tv.tv_usec, end_tv.tv_sec, 1000 * end_tv.tv_usec);
        printf("[childinfo] pid %d start %lu.%09lu end %lu.%09lu\n",\
         ch_pid, start_tv.tv_sec, 1000*start_tv.tv_usec, end_tv.tv_sec, 1000*end_tv.tv_usec);
        exit(0);
	}

	proc_assign_cpu(pid, CHILD_CPU);

	return pid;
}

int proc_block(pid_t pid){
	struct sched_param param;
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);

	if(ret < 0){
	    perror("sched_setscheduler");
	    return -1;
	}

	return ret;
}

int proc_wakeup(pid_t pid){
	struct sched_param param;
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);

	if(ret < 0){
	    perror("sched_setscheduler");
	    return -1;
	}

	return ret;
}
