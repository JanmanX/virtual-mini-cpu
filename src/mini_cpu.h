#ifndef MINI_CPU_H
#define MINI_CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "error.h"

typedef unsigned char byte;

struct mini_cpu {
	byte PC;
	byte R0;
	byte R1;
	
	char *mem;
	int mem_size;	
};

/**
 * CPU operations
**/
struct mini_cpu *new_cpu(int memory_size);
void free_cpu(struct mini_cpu*);
void cpu_reset(struct mini_cpu*);
void fetch(struct mini_cpu*); 
void decode(struct mini_cpu*, 
/**
 * Memory operations
 **/
byte mem_read(struct mini_cpu*,byte n);
void mem_write(struct mini_cpu*, byte location, byte b);
void mem_clear(struct mini_cpu*);
void mem_print(struct mini_cpu*);

#endif
