/*
purpose: A simple multi-threaded task to illustrate that threads share
         memory
Output: output from threads is displayed in the order of creation
*/ 


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void* worker(void* param);

int sum = 0;

int main(int argc, char* argv[])
{
   pthread_t tid1, tid2;  
   pthread_create(&tid1, NULL, worker, argv[1]);
   pthread_join(tid1,NULL); 

   printf("Thread1 sum = %d\n",sum);  
   return 0;
}

void* worker(void* param)
{
 int i = 1;
 int upper = atoi(param);
 
 while(i <= upper)
 {
  sum += i;
  ++i;
 }
 pthread_exit(0);
}

