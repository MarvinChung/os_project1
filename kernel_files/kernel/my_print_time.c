#include <linux/linkage.h>
#include <linux/kernel.h>
#define ULONG unsigned long

asmlinkage void sys_my_print_time(
int pid, 
ULONG start_sec,        
ULONG start_nsec,
ULONG end_sec,
ULONG end_nsec  ){
        printk("[osproj1] %d %lu.%09lu %lu.%09lu\n", pid, start_sec, start_nsec, end_sec, end_nsec);
}


