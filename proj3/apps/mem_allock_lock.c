#include<stdio.h>
#include<linux/time.h>
#include<sys/mman.h>
#define CONVERT 1E9


int main(int argc, char** argv)
{
if(argc == 0)
{
printf("Invalid format");
return 0;
}

int n = atoi(argv[1]);
char *buf = (char *)malloc(n);
int i;
struct timespec start, end;

mlock(buf, n);

clock_gettime(CLOCK_REALTIME, &start);

for(i = 0; i<n; i+=4096)
buf[i] = 1;

clock_gettime(CLOCK_REALTIME, &end);



double time_taken = ( end.tv_sec - start.tv_sec )
  + ( end.tv_nsec - start.tv_nsec )
  / CONVERT;
printf( "%lfsec\n", time_taken );

return 0;
}
