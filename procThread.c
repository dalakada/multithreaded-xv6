#include "types.h"
#include "user.h"
#include "procThread.h"


int procThread_create(void)
{
	void *stack;
	// printf(1,"%s","pthread create called \n");
	stack = (void*) malloc(4096);
	// printf(1,"Malloc address : %p \n",stack);
 //    // add your implementation here ...
 //    // return -1;
	return clone(stack);


}


void procThread_exit(int ret_val)
{
    // add your implementation here ...
    
}


void procThread_join(int tid, int * ret_val_p)
{
    // add your implementation here ...
    
}

