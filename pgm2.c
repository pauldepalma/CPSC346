//higher level  i/o and c-string processing

#include <stdio.h>
#include <string.h>

int main()
{
 char stuff[80];

 printf("Enter your email address\n");
 scanf("%s",stuff);

 printf("Your email address is %d characters long\n",strlen(stuff));
 printf("%s\n",stuff);
 return 0;
}
 

