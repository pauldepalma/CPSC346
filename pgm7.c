#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) 

{ 
	int inFile, outFile; 
	int len; char ch; 
	if (argc != 3) 
	{ 
		printf("Usage: copy <f1> <f2>\n"); 
		exit(1); 
	} 
	inFile = open(argv[1], O_RDONLY); 
	outFile = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU);
	while ((len = read(inFile, &ch, 1)) > 0) 
		write(outFile, &ch, 1);

	close(inFile); 
	close(outFile); 
	return 0; 
} 

