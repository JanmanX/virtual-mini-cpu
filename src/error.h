#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdio.h>
#include <stdlib.h>

#define error(msg) { printf("[ERROR]: In %s, %s \"\n\" ", __func__,msg);\
	exit(EXIT_FAILURE);				 \
}

#define logd(msg) {printf("[DEBUG]: In %s, %s \"\n\" ",__func__,msg);}
#endif
