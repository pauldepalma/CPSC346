#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

#define SEMKEY 0 
typedef struct sembuf sem_buf;


int main(int argc, char* argv[])
{
 int semid;
 short int in[1];
 short int out[1];

 in[0] = 1; 
 out[0]; 
 
/*create two semaphore buffers, one for wait and one for signal
The buffers have this structure:

  struct sembuf 
  {
    short sem_num;
    short sem_op;  -1 is wait, 1 is signal 
    short sem_flg;
  }
*/

 sem_buf sem_wait[1], sem_signal[1];


 //set the buffer values for wait.
 sem_wait[0].sem_num = 0;
 sem_wait[0].sem_op = -1; //decrement
 sem_wait[0].sem_flg = SEM_UNDO;   


 //set the buffer values for signal 
 sem_signal[0].sem_num = 0;
 sem_signal[0].sem_op = 1; //increment
 sem_signal[0].sem_flg = SEM_UNDO; 

 //create a semaphore set of 1  semaphore
 semid = semget(SEMKEY, 1, 0777 | IPC_CREAT);

 //initialize the first semaphore in the set identified by semid to the value in the input buffer,in
 semctl(semid, 1 , SETALL, in);

 //write the value contained in the first semaphore of the semaphore set to the output buffer,out. 
 semctl(semid, 1, GETALL, out);
 printf("semaphore values Before wait: %d\n", out[0]);

 //invoke wait on semid by using the pre-set semaphore struct
 semop(semid, sem_wait, 1);
 semctl(semid, 1, GETALL, out);
 printf("semaphore values After wait: %d\n", out[0]);

 //invoke signal on semid by the using the pre-set semaphore struct
 semop(semid, sem_signal, 1);
 semctl(semid, 1, GETALL, out);
 printf("semaphore values After signal: %d\n", out[0]);

 //cleanup by specifying that the semaphore be destroyed after the last process has detached
 //NULL can be replaced a struct-like data structure containing other operations.   
 semctl(semid, 1, IPC_RMID, NULL);
}

