/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: exF_system_call.c
Pgm Desc: Demonstrates a system call to copy a file
Usage: ./a.out file_in file_out 
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
 int inFile, outFile;
 int len;
 char ch;

 if (argc != 3)
 {
  printf("Usage: copy f1 f2\n");
 }

 //FMI, google fntl.h 
 inFile = open(argv[1],O_RDONLY);  

 //FMI google sys/stat.h
 outFile = open(argv[2],O_WRONLY | O_CREAT, S_IRWXU); 

 //read/write 1 byte into buffer whose address is stored in ch
 while ((len = read(inFile,&ch, 1)) > 0)
  {
   write(outFile,&ch,1);
  }
 close(inFile);
 close(outFile);
 return 0;
}
