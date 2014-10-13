#include "error.h"


void CPU_CHECK(void* __cpu)
{
	if(__cpu==NULL) error("cpu == NULL");
}


