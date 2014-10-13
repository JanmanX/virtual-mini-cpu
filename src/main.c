#include <stdio.h>
#include "mini_cpu.h"
int main()
{
	struct mini_cpu *cpu = new_cpu(255);

	mem_write(cpu,250, 0x0);
	mem_write(cpu,251,0x1); 

	mem_write(cpu,252, mem_read(cpu,250)+1);
	mem_write(cpu,253, mem_read(cpu,251)+1);


	mem_print(cpu);
	free_cpu(cpu);
	return 0;	
}
