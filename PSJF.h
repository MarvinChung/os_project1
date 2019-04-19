#define _GNU_SOURCE
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