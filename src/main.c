#include <stdio.h>
#include "mini_cpu.h"
int main()
{
	struct mini_cpu *cpu = new_cpu(255);

	mem_write(cpu,250, 0x0);
	mem_write(cpu,251,0x1); 

	mem_write(cpu,252, mem_read(cpu,250)+1);
	mem_write(cpu,253, mem_read(cpu,251)+1);

	/***	
	  1 1
	  2 2
	  3
	  5 12
	  6 12
	  0
	 ***/

	mem_write(cpu,1,LOAD0); 	/* R0 = 1 */
	mem_write(cpu,2,1);
	mem_write(cpu,3,LOAD1);		/* R1 = 2 */
	mem_write(cpu,4,2);
	mem_write(cpu,5,ADD);
	mem_write(cpu,6,STORE);		/* STORE R0 @ 12 */
	mem_write(cpu,7,30);
	mem_write(cpu,8,PRINT);		/* PRINT [12] */
	mem_write(cpu,9,30);
	mem_write(cpu,10,HALT);
	printf("Starting...\n");	
	run(cpu);
	printf("Complete...\n");

	mem_print(cpu);


	free_cpu(cpu);
	return 0;	
}
