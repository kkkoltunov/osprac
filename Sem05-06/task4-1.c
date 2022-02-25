#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int file;
  char output[14];
  char name[] = "test.fifo";

  if ((file = open(name, O_RDONLY)) < 0) {
    printf("{Ошибка} Не удалось открыть FIFO для чтения!\n");
    exit(-1);
  }

  size_t size = read(file, output, 14);
  if (size < 0) {
    printf("{Ошибка} Не удалось прочитать из FIFO!\n");
    exit(-1);
  }

  printf("Вывод:%s\n", output);
  if (close(file) < 0) {
    printf("{Ошибка} Не удалось закрыть FIFO!\n");
    exit(-1);
  }

  return 0;
}
