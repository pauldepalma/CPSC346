#include <stdio.h>
#include <mpi.h>

/*
 MPI assigns an integer to each process beginning with 0
 to compile: >mpicc ex24.c -o hello2
 to run: >mpirun -np 4 hello2
*/

int main(int argc, char** argv)
{
 int ierr, num_procs, my_id;

 ierr = MPI_Init(&argc, &argv); //parbegin
 ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
 ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
 printf("hello world. I'm process %i out of %i processes\n",my_id,num_procs);
 ierr = MPI_Finalize();         //parend

 return 0;
}
