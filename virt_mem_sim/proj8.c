/*
Simulated virtual memory
Your task is to introduce a page table and a translation lookaside buffer as described in
Silberschatz pp. 432-435 and in Figure 8.34
As it stands, the program does the following 25 times:
1. Reads and translates an address from addresses.txt 
2. Uses that address to read a page from BACKING_STORE.bin. This page contains
   a value that we will print out.
3. Stores the page in simulated main memory 
4. Retrives the value stored in main memory corresponding to the address
   from addresses.txt
The program also contains a sketch of page table initialization and interrogation.
You can verify the correctness of the program by comparing the output to 
correct.txt
usage: ./a.out BACKING_STORE.bin adresses.txt
*/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TLB_SIZE 16
#define PAGES 256
#define PAGE_MASK 255
#define PAGE_SIZE 256
#define OFFSET_BITS 8
#define OFFSET_MASK 255
#define MEMORY_SIZE PAGES * PAGE_SIZE 


//references to the two files used in the program
struct files
{
 char* backing;   //BACKING_STORE.bin
 FILE* ifp;       //addresses.txt
};
typedef struct files files;

//decomposed address from addresses.txt
//logical_address to components of virtual address
struct dec_addr 
{
 int logical_page;
 int offset;
};
typedef struct dec_addr dec_addr;

struct pagetable_entry
{
 char present_absent;
 int frame_number;
};
typedef struct pagetable_entry pagetable_entry;

files open_files(char* argv1,char* argv2);
dec_addr translate(FILE* ifp, int* logical_address);
int compute_physical_address(dec_addr addr,int physical_page);
void init_pagetable(pagetable_entry* pt_entry);
bool check_pagetable(pagetable_entry* pt_entry, int page_number, int* frame_number);

int main(int argc, char *argv[])
{ 
  signed char main_memory[MEMORY_SIZE];
  pagetable_entry pagetable[PAGES];
  files file_ids = open_files(argv[1],argv[2]);
  dec_addr addr;

  /*
  Sketch of page table use
  init_pagetable(pagetable);
   int frame_number; 
   if (check_pagetable(pagetable,addr.logical_page, &frame_number))
     printf("in memory\n"); 
   else
     printf("not in memory\n"); 
  */
  
  //physical_page is the page offset into main memory
  for (int physical_page = 0; physical_page < 25; physical_page++)
  {
   int logical_address;  //address read from addresses.txt
   addr = translate(file_ids.ifp,&logical_address);

   //copy from BACKING_STORE.bin to addresses.txt
   memcpy(main_memory + physical_page * PAGE_SIZE, 
          file_ids.backing + addr.logical_page * PAGE_SIZE, PAGE_SIZE);

   //the exact offset from the top of main_memory
   int physical_address = compute_physical_address(addr,physical_page); 
   signed char value = main_memory[physical_address];

       
   printf("Virtual address: %d Physical address: %d Value: %d\n", 
          logical_address, physical_address, value);
  }
    
  return 0;
}


//open files
files open_files(char* argv1, char* argv2)
{
  files file_ids;

  const char *backing_filename = argv1; 					
  int backing_fd = open(backing_filename, O_RDONLY);
  file_ids.backing = mmap(0,MEMORY_SIZE,PROT_READ,MAP_PRIVATE,backing_fd,0);
  file_ids.ifp = fopen(argv2,"r");

  return file_ids;
}

//decompose address from addresses.txt to page number and offset
dec_addr translate(FILE* ifp, int* logical_address_out)
{
 int logical_address;
 dec_addr addr; 
 fscanf(ifp,"%d", &logical_address);
 addr.offset = logical_address & OFFSET_MASK;
 addr.logical_page = (logical_address >> OFFSET_BITS) & PAGE_MASK;

 *logical_address_out = logical_address;
 return addr;
}

//determine the location of a value within main_memory
int compute_physical_address(dec_addr addr,int physical_page)
{
 return (physical_page << OFFSET_BITS) | addr.offset;
}

//initialize page table
void init_pagetable(pagetable_entry*  pagetable)
{
 for (int i = 0; i < PAGES; i++)
  pagetable[i].present_absent = 'A';
}


//interrogate page table
bool check_pagetable(pagetable_entry* pagetable, int page_number, int* frame_number) 
{
 if (pagetable[page_number].present_absent == 'A')
   return false;
 *frame_number = pagetable[page_number].frame_number;
 return true;
}
