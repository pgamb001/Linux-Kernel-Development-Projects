#include<linux/types.h>
#include<linux/unistd.h>
#include<linux/syscalls.h>
#include<linux/ktime.h>
#include<linux/hrtimer.h>
#include<linux/signal.h>
#include<linux/sched.h>
#include<linux/timer.h>

enum hrtimer_restart timer_callback(struct hrtimer *timer)
{
    printk(KERN_ERR "Callback\n");
    send_sig(SIGCONT, current, 0);
    return HRTIMER_RESTART;
}

SYSCALL_DEFINE0(wait_until_next_period)
{

struct task_struct *process_temp = current;

ktime_t kt;

if(process_temp->t.tv_sec != 0)
kt = timespec_to_ktime(process_temp->t);

else
return -1;

struct hrtimer *timer;
timer->_softexpires = kt;


timer->function = &timer_callback;
hrtimer_init(timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);

send_sig(SIGSTOP, process_temp, 0);

hrtimer_start(timer, kt, HRTIMER_MODE_ABS);

return 0;

}
