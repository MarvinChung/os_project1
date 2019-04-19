#define _GNU_SOURCE
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include "process.h"
#include "scheduler.h"

int SJF_scheduling_table(struct process *p, int nproc);