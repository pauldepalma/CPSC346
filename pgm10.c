/*
A System call 
Purpose: To demonstrate the use of a system call 
Usage: ./a.out <fileIn>  <fileOut>
Output: copies <fileIn> to <fileOut> 
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
  printf("Usage: copy <f1> <f2>\n");
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
