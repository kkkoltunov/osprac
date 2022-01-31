#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  pid_t process = fork();

  if (process  < 0) {
    printf("Error has found!\n");
  } else if (process  == 0) {
    printf("Child:\nPID: %d\nPPID: %d\n", getpid(), getppid());
  } else {
    printf("Parent:\nPID: %d\nPPID: %d\nChildPID: %d\n", getpid(), getppid(), process);
  }
  return 0;
}
