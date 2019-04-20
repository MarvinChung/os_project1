#define _GNU_SOURCE
//#include "PSJF.h"
#include "Tables.h"
//min binary heap refer to: https://www.geeksforgeeks.org/binary-heap/

// elements put in the heap
struct task {
	int t_exec; // execution time of each task
	int task_i; // task id of each task
};

static int heap_size, capacity;
static struct task *harr; // the pointer point to the heap

// to get index of parent of node at index i
static int parent(int i) { return (i-1)/2; } 
// to get index of left child of node at index i 
static int left(int i) { return (2*i + 1); } 
// to get index of right child of node at index i 
static int right(int i) { return (2*i + 2); }

// A utility function to swap two elements
static void swap(struct task *x, struct task *y) {
	struct task temp = *x;
	*x = *y;
	*y = temp;
}

static void insertKey(int k, int pid) {
	if (heap_size == capacity) {
		printf("\nOverflow: Could not insertKey\n");
		return;
	}

	// First insert the new key at the end 
	heap_size++; 
	int i = heap_size - 1; 
	harr[i].t_exec = k;
	harr[i].task_i = pid;
  
	// Fix the min heap property if it is violated 
	while (i != 0 && harr[parent(i)].t_exec > harr[i].t_exec) { 
	   swap(&harr[i], &harr[parent(i)]);
	   i = parent(i);
	} 
}

static void MinHeapify(int i) { 
	int l = left(i); 
	int r = right(i); 
	int smallest = i; 
	if (l < heap_size && harr[l].t_exec < harr[i].t_exec) 
		smallest = l; 
	if (r < heap_size && harr[r].t_exec < harr[smallest].t_exec) 
		smallest = r; 
	if (smallest != i) { 
		swap(&harr[i], &harr[smallest]); 
		MinHeapify(smallest); 
	} 
}

static struct task extractMin() {	
	if (heap_size == 1) {
		heap_size--;
		return harr[0];
	} 
  
	// Store the minimum value, and remove it from heap 
	struct task root = harr[0];
	harr[0] = harr[heap_size-1]; 
	heap_size--;
	MinHeapify(0);
  
	return root; 
}

static bool isEmpty(void) {
	return (heap_size == 0);
}

int PSJF_scheduling_table(struct process *proc, int nproc) {
	int ntask = 0;
	// malloc the heap
	harr = (struct task *) malloc(nproc * sizeof(struct task));
	capacity = nproc;
	heap_size = 0;
	int id = 0; // index of task
	int current_time = proc[0].t_ready; // start from the first task's ready time
	int temp_time = 0; // to keep how much time a task has spent
	struct process temp2 = proc[0]; // previous task extract from heap

	insertKey(proc[id].t_exec, proc[id].task_i);
	id++;
	while ( !isEmpty() || (id < nproc) ) {
		// check if the task is ready
		while (proc[id].t_ready <= current_time && id < nproc) {
			insertKey(proc[id].t_exec, proc[id].task_i);
			id++;
		}

		// extract the task with minimum execution time from heap
		struct task temp = extractMin();
		// check if the task need to execute now is different from the last task
		if (temp.task_i != temp2.task_i) {
			// if they're different, then store the data to the task_list
			task_list[ntask].pid_index = temp2.task_i;
			task_list[ntask].t_exec = temp_time;
			ntask++;

			temp2.task_i = temp.task_i;
			temp_time = 0;
		}

		temp.t_exec--;
		// if the task hasn't executed yet, put it back to the heap
		if (temp.t_exec > 0)
			insertKey(temp.t_exec, temp.task_i);
		temp_time++;
		current_time++;
	}
	// store the last task to the task_list
	task_list[ntask].pid_index = temp2.task_i;
	task_list[ntask].t_exec = temp_time;
	ntask++;

	free(harr);

	return ntask;
}