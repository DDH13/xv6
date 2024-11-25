#include "types.h"
#include "stat.h"
#include "user.h"

int main (void)
{
  printf(1, "Size of my address space is %d\n", getmysize());
  exit();
}