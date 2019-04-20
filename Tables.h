#define _GNU_SOURCE
#ifndef _TABLES_H_
#define _TABLES_H_
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdbool.h>
#include "process.h"
#include "scheduler.h"

int PSJF_scheduling_table(struct process *, int);
int RR_scheduling_table(struct process *proc, int nproc, int time);
int SJF_scheduling_table(struct process *p, int nproc);
int FIFO_scheduling_table(struct process *, int);

#endif