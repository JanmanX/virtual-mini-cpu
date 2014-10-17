Virtual mini CPU
================

Virtual CPU emulator inspired by Intel 4001.



Supported instructions
======================
HALT	/* Halts CPU 				                */
LOAD0	/* Loads byte to R0 from mem[op2] 	*/
LOAD1	/* Loads byte to R1 from mem[op2] 	*/
ADD	  /* R0 = R1 + R0 			              */
BEEP 	/* BEL 					                    */
STORE	/* Stores R0 at mem[PC] 		        */
PRINT	/* Prints mem[PC] 			            */
MOV0 	/* Sets R0 to mem[PC] 			        */
MOV1	/* Sets R1 to mem[PC] 			        */
