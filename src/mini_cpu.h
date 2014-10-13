#ifndef MINI_CPU_H
#define MINI_CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "error.h"

#define true 1
#define false 0

/* OP CODES */
#define HALT 	0x00
#define LOAD0 	0x01
#define LOAD1 	0x02
#define ADD	0x03
#define BEEP 	0x04
#define STORE	0x05
#define PRINT	0x06


typedef unsigned char byte;
typedef byte bool;


struct mini_cpu {
	byte PC;
	byte R0;
	byte R1;

	/* Control flags */
	bool _overflow;
	bool _underflow;
	bool _signed;
	bool _halt;	
		
	/* Memory */
	char *mem;
	int mem_size;
	int _reserved_address;	
	int _address_ceiling;
};


/**
 * CPU operations
**/
struct mini_cpu *new_cpu(int memory_size);
void free_cpu(struct mini_cpu*);
void cpu_reset(struct mini_cpu*);
byte fetch(struct mini_cpu*); 
void decode(struct mini_cpu*, byte op); 
void run(struct mini_cpu*);
void halt(struct mini_cpu*);
void add(struct mini_cpu*);
void store(struct mini_cpu*);
void print(struct mini_cpu*);


/**
 * Memory operations
 **/
byte mem_read(struct mini_cpu*,byte n);
void mem_write(struct mini_cpu*, byte location, byte b);
void mem_clear(struct mini_cpu*);
void mem_print(struct mini_cpu*);
#endif
