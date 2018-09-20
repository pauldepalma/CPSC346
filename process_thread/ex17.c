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
void* worker1(void* param);

int sum = 0;

int main(int argc, char* argv[])
{
   pthread_t tid1, tid2;  
   pthread_create(&tid1, NULL, worker, argv[1]);
   pthread_join(tid1,NULL); 
   printf("Thread 1 sum = %d\n",sum);  
   pthread_create(&tid2, NULL, worker1, argv[1]);
   pthread_join(tid2,NULL); 
   printf("Thread 2 sum = %d\n",sum);  

   
   return 0;
}

//This work is being done in thread 1 but not in thread 2
void* worker(void* param)
{
 int i = 0;
 int upper = atoi(param);
 
 while(i <= upper)
 {
  sum += i;
  ++i;
 }
 pthread_exit(0);
}

void* worker1(void* param)
{
 sum = sum + atoi(param);
 pthread_exit(0);
}

