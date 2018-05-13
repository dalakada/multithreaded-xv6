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
	// printf(1,"\nExit called !!!! :\n",7);
    thread_exit(ret_val);
    return;
    
}


void procThread_join(int tid, int * ret_val_p)
{
	void *stack_ptr;

	void ** ptr_to_stack_ptr;
	ptr_to_stack_ptr=&stack_ptr;

    // printf(1,"Address of original stack pointer: %d \n", &stack_ptr );

	// void join(int tid, int * ret_p, ptr_to_stack_ptr)

	join(tid,ret_val_p,ptr_to_stack_ptr);

	// for(int i =1024; i > 0 ; i--)
 //    {
 //    // current_addr= *((int *)(current_addr));
 //    	printf(1,"Address: %d  Hex: %x  Decimal: %d \n", stack_ptr, *((int *)(stack_ptr)),*((int *)(stack_ptr)));
 //    	stack_ptr=stack_ptr+4;
 //    }
    free(stack_ptr);
    
}

