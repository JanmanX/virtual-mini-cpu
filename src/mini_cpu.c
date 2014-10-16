#include "mini_cpu.h"

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

	cpu->PC = 0x01; /* Base address */
	cpu->R0 = 0;
	cpu->R1 = 0;

	cpu->_overflow = false;
	cpu->_underflow = false;
	cpu->_signed = false;
	cpu->_halt = false;
	cpu->_reserved_address = 0;
	cpu->_address_ceiling = memory_size-2;

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

	cpu->PC = 0x01; /* Base address */
	cpu->R0 = 0;
	cpu->R1 = 0;

	cpu->_overflow = false;
	cpu->_underflow = false;
	cpu->_signed = false;
	cpu->_halt = false;
	cpu->_reserved_address = 0;
	cpu->_address_ceiling = cpu->mem_size-2;

	mem_clear(cpu);
}

byte fetch(struct mini_cpu* cpu)
{
	byte opcode = 0;
	opcode = mem_read(cpu, cpu->PC++);

	if(cpu->PC > cpu->_address_ceiling) {
		halt(cpu);	
	}

	return opcode;	
}

void decode(struct mini_cpu* cpu, byte op_code)
{
	if(cpu->_halt == true) return;

	switch(op_code) {
		case HALT:
			cpu->_halt = true;
			break;

		case LOAD0:
			cpu->R0 = mem_read(cpu, cpu->PC++);
			break;

		case LOAD1:
			cpu->R1 = mem_read(cpu, cpu->PC++);
			break;

		case ADD:
			add(cpu);
			break;

		case STORE:
			store(cpu);
			break;

		case PRINT:
			print(cpu);
			break;
	}
}

void run(struct mini_cpu* cpu)
{
	cpu->PC = 0x01;

	while(cpu->_halt == false) {
		mem_write(cpu, cpu->_reserved_address, fetch(cpu));

		decode(cpu, mem_read(cpu,cpu->_reserved_address));
	}
}

void halt(struct mini_cpu* cpu)
{
	cpu->_halt = true;
}

void add(struct mini_cpu* cpu)
{
	cpu->R0 = cpu->R0 + cpu->R1;
}

void store(struct mini_cpu* cpu)
{
	cpu->R1 = mem_read(cpu, cpu->PC++);
	mem_write(cpu, cpu->R1, cpu->R0);
}

void print(struct mini_cpu* cpu)
{
	cpu->R1 = mem_read(cpu, cpu->PC++);
	cpu->R0 = mem_read(cpu, cpu->R1);
	printf("%d\n", cpu->R0);
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
		printf("%3d: 0x%02x\n",i,cpu->mem[i]);

	printf("\n");
}

void load_program(struct mini_cpu* cpu, byte* prog)
{
	int i = 0;
	byte b = 0;
	while(b = prog[i++]) {
		mem_write(cpu, i, b);
	}	
}
