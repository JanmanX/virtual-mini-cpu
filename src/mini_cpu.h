#ifndef MINI_CPU_H
#define MINI_CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "error.h"

#define true 1
#define false 0

/* 
 * opcode format:
 * OP [IMMEDIATE]
 */

/* OP CODES 							*/
#define HALT 	0x00 	/* Halts CPU 				*/
#define LOAD0 	0x01	/* Loads byte to R0 from mem[op2] 	*/
#define LOAD1 	0x02	/* Loads byte to R1 from mem[op2] 	*/
#define ADD	0x03	/* R0 = R1 + R0 			*/
#define BEEP 	0x04	/* BEL 					*/
#define STORE	0x05	/* Stores R0 at mem[PC] 		*/
#define PRINT	0x06	/* Prints mem[PC] 			*/
#define MOV0	0x07 	/* Sets R0 to mem[PC] 			*/
#define MOV1	0x08	/* Sets R1 to mem[PC] 			*/


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
void load_program(struct mini_cpu*, byte*);

#endif


