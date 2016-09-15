//pointer arithmetic, function to count words

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80

char* get_inp();

int wc(char*);

int main()
{
 char* inp = get_inp();
 int num_words = wc(inp);
 printf("%d words\n",num_words);

 free(inp);  //return dynamially allocated memory to the heap
 return 0;
}

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

int wc(char* inp)  
{
 int in_word = 0;  //in the beginning we are not in a word
 int word_ct = 0;

 while(*inp) //march down the string until you hit the null character
 {
  //if the char is white space, we are not in a word 
  if (*inp == ' ' || *inp == '\n')  
     in_word = 0; 
  else
     //if we were previously not in a word and the current character
     //is not white space, we have entered a word.  
     //Increment counter and register that we are in a word
     if (!in_word)
      {          
       in_word = 1;
       ++word_ct;
      }
  ++inp; //advance movement along the string
 }
 return word_ct;
}
