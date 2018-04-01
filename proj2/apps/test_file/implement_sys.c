#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include<stdio.h>
#include<time.h>

#define sys_set_rsv 397
#define sys_cancel_rsv 398

int main(int argc, char *argv[])
{

pid_t pid = fork();

long c = 10;
long t = 20;

struct timespec C;
struct timespec T;

C.tv_nsec = c;
T.tv_nsec = t;

if(syscall(sys_set_rsv, pid, C, T))
printf("Syscall failed");

if(pid !=0)
printf(%d,pid);

return 0;

}
