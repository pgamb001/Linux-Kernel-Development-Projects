#include<linux/types.h>
#include<linux/unistd.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE3(cancel_rsv,pid_t, pid, struct timespec*, C, struct timespec*, T)
{

//if(pid == 0)
//pid= getpid();

struct task_struct *process_temp = pid_task(find_vpid(pid), PIDTYPE_PID);

if(process_temp->c.tv_sec == 0)
return -1;

else
{ 
process_temp->c.tv_sec = 0;
process_temp->t.tv_sec = 0;
return 0;
}
}
