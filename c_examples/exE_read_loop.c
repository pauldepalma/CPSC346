/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Paul De Palma
Team Member 2: N/A 
GU Username of project lead: depalma
Pgm Name: exE_read_loop.c
Pgm Desc: Illustrates a common way to read from the keyboard in C 
Usage: ./a.out
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80

char* get_inp();

void disp_inp(char*);

int wc(char*);

int main()
{
 char* inp = get_inp();
 //printf("here is your input : %s\n",inp);

 disp_inp(inp); 
 //int num_words = wc(inp);
 //printf("%d words\n",num_words);

 free(inp);  //return dynamially allocated memory to the heap
 return 0;
}

/*
pre:  none 
post: requests a block of bytes in which to store characters 
      accepts input from the keyboard and stores them in the block
      returns the address of the block
*/

char* get_inp()
{
 char* inp = (char*) malloc(MAX_LINE);
 char* start = inp;
 char c;

 printf("Enter text <= 80 characters in length\n");
 while ((c = getchar()) != '\n')
  *inp++ = c; //weird, yes? First add the character to the dereffed pointer
              //then go to the next position in dynamic memory 
 *inp = '\0'; 
 return start;
}

/*
pre:  inp is the address of a 80 byte block of memory 
post: returns the number of words stored in the block of memory.  A word
      is any sequence of characters that 
      1) are stored at the beginning of the block or 
      2) are stored at end of the block or
      3) are terminated by the end-of-line character or
      4) are preceded by and ended by one or more spaces
        
*/
int wc(char* inp)
{}


/*
pre:  inp is the address of a 80 byte block of memory 
post: displays each character in the block 
*/
void disp_inp(char* out)
{
 while(*out)
  putchar(*out++);
 putchar('\n');
} 
