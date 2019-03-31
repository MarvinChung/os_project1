#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "process.h"
#include "scheduler.h"

//min heap base on https://www.geeksforgeeks.org/binary-heap/

struct element harr[MAX_LENGTH]; // pointer to array of elements in heap 
int capacity; // maximum possible size of min heap 
int heap_size; // Current number of elements in min heap

int parent(int i) { return (i-1)/2; } 
  
// to get index of left child of node at index i 
int left(int i) { return (2*i + 1); } 
  
// to get index of right child of node at index i 
int right(int i) { return (2*i + 2); } 

void insertKey(int k) 
{ 
    if (heap_size == capacity) 
    { 
        cout << "\nOverflow: Could not insertKey\n"; 
        return; 
    } 
  
    // First insert the new key at the end 
    heap_size++; 
    int i = heap_size - 1; 
    harr[i].t_exec = k; 
  
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
        return INT_MAX; 
    if (heap_size == 1) 
    { 
        heap_size--; 
        return harr[0]; 
    } 
  
    // Store the minimum value, and remove it from heap 
    int root = harr[0]; 
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
    int temp = *x; 
    *x = *y; 
    *y = temp; 
} 

bool isEmpty()
{
	return heap_size==1;
}
// return task_list used size
// Assume process is sorted by ready_time, if ready_time is same, sorted by exec_time
int SJF(struct process *p, int consumed_limits)
{
	//int current_time = 0;
	int e_length = 0;
	while(p++)
	{

		insertKey(p);
		struct process temp = extractMin();
		
		if( temp.t_exec > consumed_limits )
		{
			//current_time += consumed_limits;
			temp.t_exec -= consumed_limits;

			insertKey(temp);

			task_list[e_length].pid_index = p.task_i;
			task_list[e_length].t_exec = p.t_exec;
		}
		else
		{
			//current_time += temp.t_exec;
			task_list[e_length] = p.task_i;
		}

		e_length++;
	}

	while(!isEmpty())
	{
		struct process temp = extractMin();
		if( temp.t_exec > consumed_limits )
		{
			//current_time += consumed_limits;
			temp.t_exec -= consumed_limits;

			insertKey(temp);

			task_list[e_length].pid_index = p.task_i;
			task_list[e_length].t_exec = p.t_exec;
		}
		else
		{
			//current_time += temp.t_exec;
			task_list[e_length].pid_index = p.task_i;
			task_list[e_length].t_exec = p.t_exec;
		}

		e_length++;
	}
}