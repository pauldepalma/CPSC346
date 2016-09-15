/*
Purpose: To demonstrate the use of pointer with local variables
Usage: ./a.out a b
Output: b a
*/  

#include <stdio.h>

void swap(char*,char*);

int main(int argc, char* argv[])
{
 char a, b;

 //with pointers
 a = *argv[1];
 b = *argv[2];
 
 printf("original\n");
 printf("%c  %c\n",a,b);

 swap(&a,&b);
 printf("swapped\n");
 printf("%c  %c\n",a,b);
 
 //reswap
 swap(&a,&b);
 printf("reswapped\n");
 printf("%c  %c\n",a,b);

 //with a 2-D arrar
 a = argv[1][0];
 b = argv[2][0];

 printf("swapped\n");
 swap(&a,&b);
 printf("%c  %c\n",a,b);

}

void swap(char* a, char* b)
{
 char c;

  c = *a;
 *a = *b;
 *b = c;
}
