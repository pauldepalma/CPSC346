
#include <stdio.h>
#include <sys/resource.h>
#include <math.h>


int main(void)
{
  int which = PRIO_PROCESS; //interpret 2nd arg of getpriority as pid 
  id_t pid;
  int ret;
  int ct = 0;

  pid = getpid();
  ret = getpriority(which, pid);
  printf("default priority is:  %d\n", ret);
  
  setpriority(which, pid, 15);
  ret = getpriority(which, pid);
  printf("set priority to 15:  %d\n", ret);

  printf("priority set with nice:%d\n", nice());

  ret = setpriority(which, pid, 0);
  ret = getpriority(which, pid);
  printf("priority reset to default:  %d\n", ret);
  printf("Notice that it can't be done\n");

  return 0; 
}     

void do_stuff() 
{
  int ct = 0;
  while (ct++ < 1000)
    sqrt(ct);
}
