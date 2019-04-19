#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX 100000


int peek() ;

bool isEmpty() ;

bool isFull() ;

int size() ;

void insert(int data);

int pop() ;

int RR_scheduling_table(struct process *proc, int nproc, int time);
