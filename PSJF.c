#include <stdlib.h>
#include <stdio.h>
#include "process.h"
#include "scheduler.h"

int PSJF_scheduling_table(struct process *proc, int nproc)
{
	// while(count != nproc)
	// {
		ret = -1;
		for(i = 0; i < nproc; i++)
		{
			if(proc[i].pid == -1 || proc[i].t_exec == 0)
			{
				continue;
			}

			if(ret == -1 || (proc[i].t_ready <= time && proc[i].t_exec < proc[ret].t_exec))
			{
				ret = i;
			}
		}
		proc[ret].t_exec--;
		if(proc[ret].t_exec == 0)
		{
			// count++;
			printf("%d\n", ret);
		}
	// }
	return ret;
}

