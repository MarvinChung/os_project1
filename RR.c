#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX 100000

int intArray[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;

int peek() {
   return intArray[front];
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == MAX;
}

int size() {
   return itemCount;
}  

void insert(int data) {

   if(!isFull()) {
	
      if(rear == MAX-1) {
         rear = -1;            
      }       

      intArray[++rear] = data;
      itemCount++;
   }
}

int pop() {
   int data = intArray[front++];
	
   if(front == MAX) {
      front = 0;
   }
	
   itemCount--;
   return data;  
}

int RR_scheduling_table(struct process *proc, int nproc, int time)
{
    unsigned long long i=0;
    int running_p = -1;
    int running = -1;
    int exec_time = 0, ans_idx = 0;
    
    int p_count = 0;
    int *p_queue = malloc(nproc * sizeof(int));
    for(int j = 0;j<nproc;j++){
        p_queue[j] = 0;
    }

    while(1){
        if(p_count < nproc){
            for(int p = 0;p < nproc;p++){
                if(proc[p].t_ready == i && p_queue[p] == 0){
                    insert(p);
                    p_count ++;
                    p_queue[p] = 1;
                }
            }
        }

        if(!isEmpty())
        {
            if(running == -1){
                running_p = pop();
                exec_time = 0;
                task_list[ans_idx].pid_index = running_p;
                if(proc[running_p].t_exec < time){
                    task_list[ans_idx].t_exec = proc[running_p].t_exec;
                }
                else{
                    task_list[ans_idx].t_exec = time;
                }
                ans_idx ++;
                running = 0;
            }
            exec_time ++;

            if(exec_time == time){
                proc[running_p].t_exec -= time;
                running = -1;
                insert(running_p);
            }
            else if(exec_time > proc[running_p].t_exec){
                proc[running_p].t_exec = 0;
                running = -1;
            }
            
        }
        i++;
    }
    return ans_idx;
}