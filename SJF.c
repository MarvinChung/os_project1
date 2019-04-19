#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "process.h"
#include "scheduler.h"
#include <limits.h>

//min heap base on https://www.geeksforgeeks.org/binary-heap/

//#define MAXLENGTH 1000000
/*
struct element{
    int pid_index;
    int t_exec;
};

struct element task_list[MAXLENGTH];

struct process{
    char name[32];
    int t_ready, t_exec, task_i;
    pid_t pid;  
};
*/
struct process harr[MAXLENGTH]; // pointer to array of elements in heap 
int capacity = MAXLENGTH; // maximum possible size of min heap 
int heap_size = 0; // Current number of elements in min heap
void MinHeapify(int i);
void swap(struct process *x, struct process *y);

int parent(int i) { return (i-1)/2; } 
  
// to get index of left child of node at index i 
int left(int i) { return (2*i + 1); } 
  
// to get index of right child of node at index i 
int right(int i) { return (2*i + 2); } 

void insertKey(struct process *k) 
{ 
    if (heap_size == capacity) 
    { 
        puts("\nOverflow: Could not insertKey\n");
        return; 
    } 
  
    // First insert the new key at the end 
    heap_size++; 
    int i = heap_size - 1; 
    harr[i].t_exec = k->t_exec; 
    harr[i].task_i = k->task_i;
    // Fix the min heap property if it is violated 
    while (i != 0 && harr[parent(i)].t_exec > harr[i].t_exec) 
    { 
       swap(&harr[i], &harr[parent(i)]); 
       i = parent(i); 
    } 
} 
  
// Decreases value of key at index 'i' to new_val.  It is assumed that 
// new_val is smaller than harr[i]. 
void decreaseKey(int i, int new_val) 
{ 
    harr[i].t_exec = new_val; 
    while (i != 0 && harr[parent(i)].t_exec > harr[i].t_exec) 
    { 
       swap(&harr[i], &harr[parent(i)]); 
       i = parent(i); 
    } 
} 
  
// Method to remove minimum element (or root) from min heap 
struct process extractMin() 
{ 
    if (heap_size <= 0)
    {
        puts("wrong heap_size <= 0");
        exit(1);
    } 
        
    if (heap_size == 1) 
    { 
        heap_size--; 
        return harr[0]; 
    } 
  
    // Store the minimum value, and remove it from heap 
    struct process root = harr[0]; 
    harr[0] = harr[heap_size-1]; 
    heap_size--; 
    MinHeapify(0); 
  
    return root; 
} 
  
  
// This function deletes key at index i. It first reduced value to minus 
// infinite, then calls extractMin() 
void deleteKey(int i) 
{ 
    decreaseKey(i, INT_MIN); 
    extractMin(); 
} 
  
// A recursive method to heapify a subtree with the root at given index 
// This method assumes that the subtrees are already heapified 
void MinHeapify(int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < heap_size && harr[l].t_exec < harr[i].t_exec) 
        smallest = l; 
    if (r < heap_size && harr[r].t_exec < harr[smallest].t_exec) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&harr[i], &harr[smallest]); 
        MinHeapify(smallest); 
    } 
} 
  
// A utility function to swap two elements 
void swap(struct process *x, struct process *y) 
{ 
    struct process temp = *x; 
    *x = *y; 
    *y = temp; 
} 

bool isEmpty()
{
	return heap_size==0;
}
// return task_list used size
// Assume process is sorted by ready_time, if ready_time is same, sorted by exec_time
int SJF_scheduling_table(struct process *p, int nproc)
{
    //int consumed_limits = 0xffffffff;
	//int current_time = 0;
	int e_length = 0;
	for (int i =0 ;i < nproc; i++, p++)
	{
        //puts("before insertKey");
		insertKey(p);
		//puts("after insertKey");
        struct process temp = extractMin();
		//puts("after extractMin");
		// if( temp.t_exec > consumed_limits )
		// {
		// 	//current_time += consumed_limits;
		// 	temp.t_exec -= consumed_limits;

		// 	insertKey(&temp);

		// 	task_list[e_length].pid_index = temp.task_i;
		// 	task_list[e_length].t_exec = temp.t_exec;
		// }
		// else
		// {
		//current_time += temp.t_exec;
		task_list[e_length].pid_index = temp.task_i;
        task_list[e_length].t_exec = temp.t_exec;
		// }

		e_length++;
	}

	// while(!isEmpty())
	// {
	// 	struct process temp = extractMin();
	// 	if( temp.t_exec > consumed_limits )
	// 	{
	// 		//current_time += consumed_limits;
	// 		puts("A");
 //            temp.t_exec -= consumed_limits;

	// 		insertKey(&temp);
 //            puts("B");
	// 		task_list[e_length].pid_index = temp.task_i;
	// 		task_list[e_length].t_exec = temp.t_exec;
	// 	}
	// 	else
	// 	{
	// 		//current_time += temp.t_exec;
 //            puts("C");
	// 		task_list[e_length].pid_index = temp.task_i;
	// 		task_list[e_length].t_exec = temp.t_exec;
	// 	}

	// 	e_length++;
	// }
	return e_length;
}
