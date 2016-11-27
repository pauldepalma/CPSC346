/*
Basics of program needed to complete assignment 7
This example processes the first virtual address stored in addresses.txt
The output should be identical to the first line of correct.txt
*/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define TLB_SIZE 16
#define PAGES 256
#define PAGE_MASK 255
#define PAGE_SIZE 256
#define OFFSET_BITS 8
#define OFFSET_MASK 255
#define MEMORY_SIZE PAGES * PAGE_SIZE 


/*
********Important Types, Data Structures and Variables************************ 
Structs
tlb: struct representing an entry in translation lookaside buffer 
virtAddress: struct representing the page offset within the page table and displacement within page

Storage
backing: pointer to memory mapped secondary storage
main_memory: array of signed chars simulating RAM

Tables
tlBuf: array of type tlb representing the translation lookaside buffer
tlbindex: index into tlBuf
pagetable: array of ints simulating the page table

Counters
numPageRefs: number of page table references
numPageFaults: counts number of page faults
numTLBRefs: number of TLB tries
numTLBHits: number of TLB references that resutled in a hit

Addresses 
logical_address: address read from disk, simulating an address reference 
virtualAddress: variable of type virtAddress. Parse of logical_address into page number and offset
physical_page: page frame number
logical_page: page table number
offset: displacement within page table/frame 

Output
Virtual address: logical_address, in Addresses, above
Physical address: physical_page in Addresses, above 
value: value stored in main_memory at physical_page displacement plus offset
*/

struct tlbentry 
   {
    unsigned char logical;
    unsigned char physical;
   };
typedef struct tlbentry tlb;  

struct virtAddress 
   {
    int logical_page;  //page/frame number 
    int offset;
   };
typedef struct virtAddress virtualAddress;  


int main(int argc, char *argv[])
{ 
  int pagetable[PAGES];
  tlb tlBuff[TLB_SIZE];
  int tlbindex = 0;
  signed char main_memory[MEMORY_SIZE];
  signed char *backing;
  int logical_address;
  int offset;
  int logical_page;
  int physical_page;
  int physical_address;
  int numPageFaults = 0;
  int numPageRefs = 0;
  int numTLBRefs = 0;
  int numTLBHits = 0;

  //open simulation of secondary storage     
  const char *backing_filename = argv[1]; //BACKING_STORE.bin 
  int backing_fd = open(backing_filename, O_RDONLY);
  //after the next instruction the secondary storage file can be viewed as an array
  backing = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, backing_fd, 0); 

  //open simulation of address bus and read the first line 
  FILE *ifp = fopen(argv[2],"r"); //addresses.txt 
  fscanf(ifp,"%d", &logical_address);

  //extract low order 8 bits from the logical_address. This is the offset
  offset = logical_address & OFFSET_MASK;

  //extract bits 8 through 15. This is the page number by shifting right 8 bits 
  logical_page = (logical_address >> OFFSET_BITS) & PAGE_MASK;

  //When you write the program, the physical page will increment by 1 for each copy
  //from simulated backing store to main memory 
  physical_page = 0; 

  //copy from secondary storage to simulated RAM. The address on secondary storage
  //as an offset into the memory map, backing, computing by multiplying the logical
  //page number by 256 and adding the offset 
  memcpy(main_memory + physical_page * PAGE_SIZE, 
           backing + logical_page * PAGE_SIZE, PAGE_SIZE);

  //Shift the physical page left 8 bits and or with the offset
  physical_address = (physical_page << OFFSET_BITS) | offset;

  //extract the value store at offset bytes within the page
  signed char value = main_memory[physical_page * PAGE_SIZE + offset];
       
  printf("Virtual address: %d Physical address: %d Value: %d\n", 
          logical_address, offset, value);
    
  return 0;
}
