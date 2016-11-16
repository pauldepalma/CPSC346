/*
Basics of program needed to complete assignment 7
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

// Max number of characters per line of virtual address file to be read (addresses.txt) 
#define BUFFER_SIZE 10

struct tlbentry {
    unsigned char logical;
    unsigned char physical;
};

// TLB is kept track of as a circular array, with the oldest element being overwritten once 
//the TLB is full.
struct tlbentry tlb[TLB_SIZE];

//number of inserts into TLB that have been completed. Use as tlbindex % TLB_SIZE for 
//the index of the next TLB line to use.
int tlbindex = 0;

// pagetable[logical_page] is the physical page number for logical page. Value is -1 
// if that logical page isn't yet in the table.
int pagetable[PAGES];

//simulation of RAM
signed char main_memory[MEMORY_SIZE];

// Pointer to memory mapped secondary storage 
signed char *backing;


int main(int argc, const char *argv[])
{
    const char *backing_filename = argv[1]; 
    int backing_fd = open(backing_filename, O_RDONLY);
    //after the next instruction the secondary storage file can be viewed as an array
    backing = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, backing_fd, 0); 
    
    int logical_address = 16916;  //The first line of addresses.txt

    //extract low order 8 bits from the logical_address. This is the offset
    int offset = logical_address & OFFSET_MASK;

    //extract bits 8 through 15. This is the page number 
    int logical_page = (logical_address >> OFFSET_BITS) & PAGE_MASK;
        
    int physical_page = 64; //Page at logical address 16916 will be the 65th page in RAM 

    //copy from secondary storage to simulated RAM. The address on secondary storage
    //as an offset into the memory map, backing, computing by multiplying the logical
    //page number by 256 and adding the offset 

    memcpy(main_memory + physical_page * PAGE_SIZE, 
           backing + logical_page * PAGE_SIZE, PAGE_SIZE);

    //Shift the physical page left 8 bits and or with the offset
    int physical_address = (physical_page << OFFSET_BITS) | offset;
    signed char value = main_memory[physical_page * PAGE_SIZE + offset];            
    printf("Virtual address: %d Physical address: %d Value: %d\n", 
            logical_address, physical_address, value);
    
    return 0;
}
