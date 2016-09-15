//simple character i/o

#include <stdio.h>

int main()
{
 char c;
 
 printf("Enter some text\n");
 while ((c = getchar()) != '\n')
 {
  putchar(c);
 }
 putchar('\n');
 return 0;
}
 

