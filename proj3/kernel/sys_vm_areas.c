#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/mm.h>
#include<linux/syscalls.h>
#include<linux/unistd.h>

SYSCALL_DEFINE1(show_vm_areas, int, pid)
{
struct mm_struct *tempmm;
struct vm_area_struct *vmarea;
struct task_struct *task;
unsigned long pfn;
int count,i;
for_each_process(task)
{
if(task->pid == pid)
tempmm = task->mm;
}

if(tempmm == NULL)
return -1;

printk(KERN_INFO "[Memory-mapped areas of process %d]\n", pid);
for(vmarea = tempmm->mmap; vmarea; vmarea = vmarea->vm_next)
{
printk(KERN_INFO "%lx - %lx : %lx bytes ", vmarea->vm_start, vmarea->vm_end, vmarea->vm_end - vmarea->vm_start);
if(vmarea->vm_flags & VM_LOCKED)
printk(KERN_INFO "[L]");
count = 0;
if(vmarea->vm_start > vmarea->vm_end)                                 //To account for whether vm area expands from bottom to top, or top to bottom
{
for(i = vmarea->vm_start ; i = vmarea->vm_end; i+=100000)
if(follow_pfn(vmarea, i, pfn)==0)					//Follow the vm address to get the pfn, if it returns non-zero, page does not exist
count++;
}
else
{
for(i = vmarea->vm_start ; i = vmarea->vm_end; i-=100000)
if(follow_pfn(vmarea, i, pfn)==0)
count++;
}
printk(KERN_INFO "%d Pages in physical memory\n", count);
}

return 0;
}
