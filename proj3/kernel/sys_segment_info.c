#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/mm.h>
#include<linux/syscalls.h>
#include<linux/unistd.h>

SYSCALL_DEFINE1(show_segment_info, int, pid)
{
struct mm_struct *tempmm;
struct task_struct *task;

for_each_process(task)
{
if(task->pid == pid)
tempmm = task->mm;
}

if(tempmm == NULL)
return -1;

printk(KERN_INFO "[Memory segment addresses of process %d]\n",pid);
printk(KERN_INFO "%lx - %lx: code segment\n", tempmm->start_code, tempmm->end_code);
printk(KERN_INFO "%lx - %lx: data segment\n", tempmm->start_data, tempmm->end_data);
printk(KERN_INFO "%lx - %lx: heap segment\n", tempmm->start_brk, tempmm->brk);


return 0;
}
