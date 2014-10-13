#include "mini_cpu.h"

typedef unsigned char byte;

struct mini_cpu *new_cpu(int memory_size)
{
	struct mini_cpu *cpu=(struct mini_cpu*)malloc(
			sizeof(struct mini_cpu));

	CPU_CHECK(cpu);

	byte *mem = (byte*)calloc(memory_size, sizeof(byte));
	if(mem == NULL) {
		free(cpu);
		error("Could not allocate memory");
	}

	cpu->mem = mem;
	cpu->mem_size = memory_size;
	return cpu;
}

void free_cpu(struct mini_cpu* cpu)
{
	if(cpu==NULL) return;
	free(cpu->mem);
	free(cpu);	
}

void cpu_reset(struct mini_cpu * cpu)
{
	CPU_CHECK(cpu);

	cpu->PC = 0;
	cpu->R0 = 0;
	cpu->R1 = 0;
	mem_clear(cpu);
}

byte fetch(struct mini_cpu* cpu)
{
	byte opcode = 0;
	opcode = mem_read(cpu, cpu->PC++);
	return opcode;	
}

/**
 * Memory operations
 **/

byte mem_read(struct mini_cpu* cpu, byte n)
{
	CPU_CHECK(cpu);
	return cpu->mem[n];
}

void mem_write(struct mini_cpu *cpu, byte n, byte b)
{
	CPU_CHECK(cpu);

	if(b > UCHAR_MAX) {
		b = UCHAR_MAX;
		logd("Cannot write a value bigger than 255 to memory");
	}

	if(n >= cpu->mem_size) 
		error("In mem_write(), Cannot write to location");

	cpu->mem[n] = b;
}

void mem_clear(struct mini_cpu * cpu)
{
	CPU_CHECK(cpu);

	memset(cpu->mem, 0, cpu->mem_size);	
}

void mem_print(struct mini_cpu *cpu)
{
	CPU_CHECK(cpu);

	printf("CPU memory: \n");

	int i = 0;
	for(; i < cpu->mem_size; ++i)
		printf("%d:\t 0x%02x\t ",i,cpu->mem[i]);
}
