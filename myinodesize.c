#include "types.h"
#include "stat.h"
#include "user.h"


// Takes the path of a file or folder and returns size of a given inode in bytes.
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf(2, "Usage: myinodesize path\n");
    exit();
  }
  printf(1, "Size of a given inode: %d\n", getinodesize(argv[1]));
  exit();
}