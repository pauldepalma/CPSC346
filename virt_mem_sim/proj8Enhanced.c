/*
Basics of program needed to complete assignment. 
This example processes the first logical address stored in addresses.txt.
With this address, the program:
1) Decomposes (translates) the address to page number and offset
2) Reads the page found at page number * the size of the page
3) Stores that page in simulated ram
4) Reads the value stored in simulated ram offset bytes from the top of the page
5) Displays the logical address, the offset into the page from 3, and the value found there.


Your task is to complete the program for all virtual adresses in addresses.txt.  
Think of a loop reading addresses.txt as a memory bus passing logical address to a program. 

See Figure 8.34 on p. 433.   The page number/offset block is what comes from addresses.txt.   
Here are the conditions that must be accounted for:

1. logical addreess is in TLB 
2. logical address in not in TLB but is in memory
3. logical address is neither in TLB nor in memory

Note that TLB is extra credit

Here's the structure of the program

while(there are more logical addresses)
{
 translate the page number and offset from the logical address. 
 Search the TLB for the page number.
 If the page number is in the TLB, add the offset to the frame number found in the TLB.  
 Use the result to extract data from memory.
 Print out according to instructions in the text. 
 If the page number is not in the TLB, use the page number as an offset into the page table.
 If the page number is in the page table, put the page number and the frame number in the TLB. 
 Use the result to extract data from memory.
 Print out according to instructions in the text. 
 If the page number is not in the page table, bring the page in from BACKING_STORE.bin. 
 You do this by translating the tranlsating the address, just as I do in the example below.
 Add the result to memory.
 Update the page table and TLB.   
 Print out according to instructions in the text. 
}

This program simulates demand paging.  This means that memory is initially empty.  
Since memory is the same size as BACKING_STORE, you do not have to handle page replacement. 
TLB is another story.  If you access a page that is not in TLB and TLB is full, 
you must evict an entry in the TLB.  
This means you need an eviction strategy.  Use LRU.  
There is an integer in the TLB that will store the most recent address reference.
For example, there are 1000 addresses stored in addresses.txt.  If you get a TLB  hit 
(or store an entry in the TLB) on 77th counting from 0, store 77 in the TLB struct for that page.  
If you need to evict a page from the TLB, overwrite the TLB entry with the lowest associated number. 
*/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  //allows use of bool type

#define TLB_SIZE 16
#define PAGES 256
#define PAGE_MASK 255
#define PAGE_SIZE 256
#define OFFSET_BITS 8
#define OFFSET_MASK 255
#define MEMORY_SIZE PAGES * PAGE_SIZE 




//single entry in the page table.  present_absent = 'A' page not in RAM.  
//present_absent = 'P' page in RAM
struct pagetable_entry 
   {
    char present_absent; 
    char frame_number;
   };
typedef struct pagetable_entry pagetable_entry; 


//single entry in the translation lookaside buffer.  
//tlb_ref holds the number of page the fault.  Used to implement LRU
struct tlb_entry 
   {
    char page_number;
    char frame_number;
    int tlb_ref;
   };
typedef struct tlb_entry tlb_entry;  

//decomposed entry from addresses.txt
struct virt_addr 
   {
    char page_number;
    char offset; 
   };
typedef struct virt_addr virt_addr;  

//file references
struct files
{
  char* backing;         //reference to secondary storage (BACKING_STORE.bin)
  FILE* fin;             //reference to address bus (addresses.txt)
};
typedef struct files files;
  
//function prototypes
void init_pagetable(pagetable_entry*);
void init_tlb(tlb_entry*);
files open_files(char*, char*);
void  translate(files, virt_addr*, int*);
char write_read_memory(char*, virt_addr*, files, int*);
bool check_pagetable(pagetable_entry*,virt_addr,char*);
bool check_tlb(tlb_entry*,virt_addr,char*);
void display_values(int, int, char);

int main(int argc, char *argv[])
{ 
  int logical_address;  	       //address from addresses.txt
  virt_addr virtual_address;           //holds page number and offset from logical_address
  int physical_address;                //offset into page frame 
  pagetable_entry pagetable[PAGES];    //page table
  tlb_entry tlb[TLB_SIZE];             //translation lookaside buffer
  char main_memory[MEMORY_SIZE];       //RAM
  files file_ids;                      //identifiers for the two files used in the program

  init_pagetable(pagetable);

  init_tlb(tlb);

  file_ids = open_files(argv[1],argv[2]);

  translate(file_ids,&virtual_address,&logical_address);    

  char value = write_read_memory(main_memory, &virtual_address,file_ids,&physical_address);

  //The next two function calls demonstrate how the pagetable and tlb might be interrogated
  char frame_number;
  if (check_tlb(tlb,virtual_address,&frame_number))
     printf("page reference in translation lookaside buffer\n");
  else
     printf("page reference not in translation lookaside buffer\n");

  if (check_pagetable(pagetable,virtual_address,&frame_number))
     printf("page reference in page table\n");
  else
     printf("page reference not in page table\n");
    

  display_values(logical_address, physical_address, value);

  return 0;
}

//Init page table.  Set absent field to 'A'
void init_pagetable(pagetable_entry* pagetable)
{
 for (int i = 0; i < PAGES; i++)
       pagetable[i].present_absent = 'A';
} 

//Init tlb. Set page_number field to -1 (i.e., empty) 
void init_tlb(tlb_entry* tlb)
{
 for (int i = 0; i < TLB_SIZE; i++)
       tlb[i].page_number = -1;
}

//open and prepare files
files open_files(char* argv_1, char* argv_2)
{ 
  files ids;

  //allow BACKING_STORE.bin to be treated as an array
  int backing_fd = open(argv_1, O_RDONLY);  //open BACKING_STORE.bin
  ids.backing = mmap(0,MEMORY_SIZE, PROT_READ, MAP_PRIVATE, backing_fd, 0);

  ids.fin = fopen(argv_2,"r"); //open addresses.txt
  return ids;

}

//read and translate address 
void translate(files ids, virt_addr* virt_address, int* logical_address_out)
{
 int logical_address;    //the value stored in address.txt 
 fscanf(ids.fin,"%d", &logical_address);
 virt_address->page_number = (logical_address >> OFFSET_BITS) & PAGE_MASK;
 virt_address->offset = logical_address & OFFSET_MASK;
 *logical_address_out = logical_address;
}

//copy backing store to main memory
//read sought after value from offset into memory
char write_read_memory(char* main_memory,  virt_addr* virtual_address, files file_ids, 
		int* physical_address)
{
 int frame_number  = 0;
 memcpy(main_memory + frame_number * PAGE_SIZE,
		 file_ids.backing + virtual_address->page_number * PAGE_SIZE, PAGE_SIZE);

 //offset into page frame 
 *physical_address = (frame_number << OFFSET_BITS) | virtual_address->offset; 
 char value = main_memory[*physical_address * PAGE_SIZE + virtual_address->offset];
 return value;
}

//interrogate page table
bool check_pagetable(pagetable_entry* pagetable, virt_addr virtual_address, char* frame_number)
{
 if (pagetable[virtual_address.page_number].present_absent == 'A')
   return false;
 *frame_number = pagetable[virtual_address.page_number].frame_number;
 return true; 
}

//interrogate tlb
bool check_tlb(tlb_entry* tlb, virt_addr virtual_address,char* frame_number)
{
 for (int i = 0; i < TLB_SIZE; i++)
   if (tlb[i].page_number == virtual_address.page_number)
    {
     *frame_number = tlb[i].frame_number;
     return true; 
    }
 return false;
}

void display_values(int logical_address, int physical_address, char value)
{
 printf("Virtual address: %d Physical address: %d Value: %d\n",
		 logical_address, physical_address, value);
}
