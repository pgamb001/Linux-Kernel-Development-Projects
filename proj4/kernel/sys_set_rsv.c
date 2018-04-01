#include<linux/types.h>
#include<linux/unistd.h>
#include<linux/syscalls.h>
#include<linux/sched.h>
#include<linux/slab.h>
#include<asm/div64.h>
//:#define CEILING(x,y) do_div((x + y - 1),y)
SYSCALL_DEFINE4(set_rsv,pid_t, pid, struct timespec*, C, struct timespec*, T, int, cpuid)
{

struct cpumask *current_mask;
//Note: priority is set as : highest priority task has (int custom_prio) variable in task_struct as maximum




//assign cpu to task
if(cpuid >= 4)
return -1;

int cpu_space[4];

struct timespec* timetemp;

struct task_struct *task;

if(cpuid == -1)
{
for_each_process(task)
{
if(task->t.tv_nsec!=0)
cpu_space[task_cpu(task)]++;
}
}
int k;
int cpu_least = 0;

for(k = 0; k < 4; k++)
if(cpu_least > cpu_space[k])
cpuid = k;


cpumask_clear(current_mask);
cpumask_set_cpu(cpuid, current_mask);
sched_setaffinity(pid, current_mask);

//find task_struct of task by pid passed in system call
struct task_struct *process_temp = pid_task(find_vpid(pid), PIDTYPE_PID);

//assign c and t 
if(process_temp->t.tv_sec == 0)
{ 
process_temp->c.tv_nsec = C->tv_nsec;
process_temp->t.tv_nsec = T->tv_nsec;
}
else
{
return -1;
}
//find period of already existing task that is just less than that of task to be added to scheduler
struct task_struct *task_max;
for_each_process(task)
{
if(cpuid == task_cpu(task) && task->t.tv_nsec != 0)
{
if(task->t.tv_nsec < T->tv_nsec && task->t.tv_nsec > task_max->t.tv_nsec)
task_max = task;
}
}

//decrement priority of all tasks with period less than task_max to make room for new insertion of task
for_each_process(task)
{
if(cpuid == task_cpu(task))
{
if(task->custom_prio < task_max->custom_prio)
task->custom_prio = (task->custom_prio) - 1; 
}
}

//insert new task and assign its priority
process_temp->custom_prio = (task_max->custom_prio) - 1;



//check schedulability with the addition of new task
int count;
for_each_process(task)
{
if(cpuid == task_cpu(task) && task->custom_prio > process_temp->custom_prio && task->t.tv_nsec != 0)
count++;
}
long long int *C_temp = (long long int*)kmalloc(count*sizeof(long long int*), GFP_USER); //to store C values for all tasks that have reservations on that particular CPU
long long int *T_temp = (long long int*)kmalloc(count*sizeof(long long int*), GFP_USER); //to store T values for all tasks that have reservations on that particular CPU

int i,j;
i = 0;
j = 0;
for_each_process(task)
{
if(cpuid == task_cpu(task) && task->custom_prio > process_temp->custom_prio)
{
C_temp[i] = task->c.tv_nsec;
T_temp[i] = task->t.tv_nsec;
}
}
long int *R = (long int*)kmalloc(count*sizeof(long int*), GFP_USER);
long long int temp;
int temp2;
while(R[i] != R[i-1] && i<count)
{
if(i == 0)
R[i] = process_temp->c.tv_nsec;
else
for(j = 0;j < count; j++)
{
temp = R[j] + T_temp[j] - 1;
temp2 = T_temp[j];
R[i] = process_temp->c.tv_nsec + do_div(temp, temp2)*C_temp[j];
}
i++;
} 

if(R[i] <= T->tv_nsec)
{
kfree(R);
kfree(T_temp);
kfree(C_temp);
return 0;
}
else 
{
kfree(R);
kfree(T_temp);
kfree(C_temp);
process_temp->c.tv_nsec = 0;
process_temp->t.tv_nsec = 0;
for_each_process(task)
{
if(cpuid == task_cpu(task))
{
if(task->custom_prio < task_max->custom_prio && task->t.tv_nsec != 0)
task->custom_prio = (task->custom_prio) + 1; 
}
}
return -1;
}
}
