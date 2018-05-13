#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

extern int free_frame_cnt; // CS550

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
// int sys_shutdown(void)
// {
//   /* Either of the following will work. Does not harm to put them together. */
//   outw(0xB004, 0x0|0x2000); // working for old qemu
//   outw(0x604, 0x0|0x2000); // working for newer qemu

//   return  0;
// }
int sys_print_free_frame_cnt(void)
{
    cprintf("free-frames %d\n", free_frame_cnt);
    return 0;
}
void
sys_shutdown(void)
{
  return shutdown();
}
int sys_clone(void)
{
  void* stack;
  argptr(0, (void*) &stack, 4096);

  return clone(stack);
  
}
void sys_join()
{
  int tid;
  argint(0, &tid);

  int* ret_p;
  argptr(1, (char**)&ret_p, 4);

  void ** stack;
  argptr(2, (void*) &stack, 4);

  return join(tid,ret_p,stack);
  
}
void sys_thread_exit (void)
{
  int ret_val;
  argint(0, &ret_val);
  return thread_exit(ret_val);

}


// int sys_clone(void)
// return clone();