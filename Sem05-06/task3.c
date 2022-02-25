#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
  int fd[2];
  int full = 0;
  int counter_pipes = 0;

  if (pipe2(fd, O_NONBLOCK) < 0) {
    printf("{Ошибка} Не удалось открыть pipe!\n");
    exit(-1);
  }

  while (!full) {
    if (write(fd[1], "p", 1) > 0) {
      ++counter_pipes;
    } else {
      full = 1;
    }
  }

  printf("Размер pipe = %d\n", counter_pipes);
  if (close(fd[0]) < 0) {
    printf("{Ошибка} Не удалось закрыть чтение pipe!\n");
    exit(-1);
  }
  if (close(fd[1]) < 0) {
    printf("{Ошибка} Не удалось закрыть запись pipe!\n");
    exit(-1);
  }

  return 0;
}
