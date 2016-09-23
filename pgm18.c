/*
pthread_join 
purpose: demonstrate how to synchronize threads.
Output: output from threads is displayed in the order of creation
*/ 


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void* print_hello_world(void*);


int main(int argc, char* argv[])
{
   pthread_t threads[NUM_THREADS];  

   int status, i;

  for (i = 0; i < NUM_THREADS; i++)
  {
    printf("In Main.  Creating thread %d\n", i);
    status = pthread_create(&threads[i], NULL, print_hello_world, (void*)i );
    pthread_join(threads[i],NULL); //wait for thread[i] to complete 
  }
  if (status != 0)
  {
    printf("Error in thread %d: %d\n", i, status);
    exit(-1);
  }
  return 0; 
}

void* print_hello_world(void* tid)
{
 printf("Hello from thread %d\n",(int)tid);
 pthread_exit(NULL);
}
