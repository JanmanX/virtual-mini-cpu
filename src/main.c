#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "mini_cpu.h"

int main(int argc, char **argv)
{
	if(argc < 2) {
		printf("Supply this program with assembly code!\n");
		return 0;
	}

	struct mini_cpu *cpu = new_cpu(255);

	byte* prog = (byte*)calloc(255, sizeof(byte));
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		printf("Could read from source program!\n");
		return 0;
	}

	int c = read(fd, prog, 255);
	close(fd);
	printf("%d bytes read. Starting CPU...\n",c);
	
	printf("Printing program:\n");
	int i = 0;
	for(; i < c; ++i)
		printf("0x%x\t", prog[i]);
	printf("\n");

	load_program(cpu, prog, c);
	run(cpu);

	mem_print(cpu);	

	free_cpu(cpu);
	return 0;	
}
