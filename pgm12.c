/*
more file operations
Purpose: To demonstrate conversion of strings to integers with scanf
Usage: ./a.out input_file output_file
Outpus: output_file holds the sum of the integers encoded in the input file. 
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
 FILE *ifp, *ofp;
 int sum = 0;
 int num = 0; 

 ifp = fopen(argv[1],"r");
 ofp = fopen(argv[2],"w");

 while (fscanf(ifp, "%d", &num) == 1)
  sum += num;
 fprintf(ofp, "The sum is %d\n", sum);

 fclose(ifp);
 fclose(ofp);
 return 0;
} 
