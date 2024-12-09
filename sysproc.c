#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
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
    if(myproc()->killed){
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

// return the year when Unix was created
int
sys_getyear(void)
{
  return 1975;
}

// return the size of the address space
int
sys_getmysize(void)
{
  return myproc()->sz;
}

// return the starting vritual address of the kernel area
int 
sys_getkernelstartaddr(void)
{
  return KERNBASE;
}

// return the ending virtual address of the kernel area
int
sys_getkernelendaddr(void)
{
  return KERNBASE + PHYSTOP;
}

// Create an int variable and return its address
int
sys_getkernelvariaddr(void)
{
  int a = 420;
  int b = (int) &a;
  return b;
}

// return the address of the sys_fork system call
int
sys_getsytemcalladdr(void)
{
  return (int) sys_fork;
}

// take an integer and set priority of a process and stop ones with priority 2 from running
int
sys_setpriority(int priority){
  if(argint(0, &priority) < 0)
    return -1;
  else if(priority < 0 || priority > 2)
    return -1;
  myproc()->priority = priority;
  return 0;
}