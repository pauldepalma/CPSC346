//Demonstrates scope of thread scheduling

#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void* runner(void*);
void get_scope(pthread_attr_t*); 

int main()
{
 int i;
 pthread_t tid[NUM_THREADS];
 pthread_attr_t attr;

 //get default attributes
 pthread_attr_init(&attr);

 printf("default scope\n");
 get_scope(&attr); 

 //set scheduler to process scope or system scope
 //pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
 pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS); 

 printf("after setting scope\n"); //unix permits only system level scheduling
 get_scope(&attr); 

 //create the threads
 for (i = 0; i < NUM_THREADS; i++)
   pthread_create(&tid[i], &attr, runner, (void*)i);

 //join on each thread
 for (i = 0; i < NUM_THREADS; i++)
    pthread_join(tid[i],  NULL);
}


/*Do some work*/
void* runner(void* tid)
{
 printf("Hello from thread %d\n",(int)tid);
 pthread_exit(NULL);
} 

/*Get Scope*/
void get_scope(pthread_attr_t* attr)
{
 int scope;
 if (pthread_attr_getscope(attr,&scope) != 0)
   fprintf(stderr, "unable to get scope\n");
 else
   {
    if (scope == PTHREAD_SCOPE_PROCESS) //scheduling at user level
      printf("THREAD_SCOPE_PROCESS\n");
    else
      if (scope == PTHREAD_SCOPE_SYSTEM) //scheduling at kernel level
        printf("THREAD_SCOPE_SYSTEM\n");
      else
        fprintf(stderr, "Illegal scope value\n");
   }
}
