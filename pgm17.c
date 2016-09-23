/*
Threads
Purpose: To demonstrate that threads are independently scheduled.
Notes:
  It is necessary to install the pthreads package.  On Lubuntu:
  sudo apt-get install libpthread-stubs0-dev
  It is necessary to link in the pthread library:
To compile: gcc -o ex11 ex11.c -lpthread
Usage: ex11
Output:output from theads is displayed asynchronously 

*/


#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

/*
a void pointer in c can store an address of any type.  It is 
a C convention for a raw address.  A void pointer takes on the
type of the pointer assigned to it.  You can see this as a great
liberation, but also as a potential problem
*/
void* print_hello_world(void*);


int main(int argc, char* argv[])
{
  pthread_t threads[NUM_THREADS]; //create an arrary of thread identifiers 

  int status, i;

  for (i = 0; i < NUM_THREADS; i++)
  {
    printf("In Main.  Creating thread %d\n", i);
    /*
    1) i is the thread number/id
    2) NULL says accept default attributes
    3) print_hollow_world is the function to execute
    4) i is the parameter to  print_hello_world
    */
    status = pthread_create(&threads[i], NULL, print_hello_world, (void*)i );
  }
  if (status != 0)
  {
    printf("Error in thread %d: %d\n", i, status);
    exit(-1);
  }
  //try commenting out the next line
  sleep(3); //prevent program from exiting before thread creation
  return 0; 
}

void* print_hello_world(void* tid)
{
 printf("Hello from thread %d\n",(int)tid);
 pthread_exit(NULL);
}
