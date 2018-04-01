#include<stdio.h>
#include<linux/unistd.h>



int main(int argc, char *argv[])
{
if(argc != 5)
return 0;

int pid, C, T, cpuid;

pid = atoi(argv[1]);
C = atoi(argv[2]);
T = atoi(argv[3]);
cpuid = atoi(argv[4]);
C = C*1000000;
T = T*1000000;

syscall(397, pid, C, T, cpuid);
 

return 0;
}
