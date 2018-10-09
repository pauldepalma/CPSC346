#include <stdio.h>
#include <mpi.h>

/*
requrires that several libraries be installed
sudo apt install lam4-dev
sudo apt install libmpich-dev
sudo apt install libopenmpi-dev

to compile: >mpicc ex23.c -o hello
to run: >mpirun -np 4 hello

forks off four processes, each of which outputs "hello."
*/

int main(int argc, char** argv)
{
 int ierr;
 ierr = MPI_Init(&argc, &argv); //parbegin
 printf("hello world\n");
 ierr = MPI_Finalize();         //parend

 return 0;
}
