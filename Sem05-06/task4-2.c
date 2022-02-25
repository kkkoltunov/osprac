#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int file;
  char name[] = "test.fifo";

  (void)umask(0);
  if (mknod(name, S_IFIFO | 0666, 0) < 0) {
    printf("{Ошибка} Не удалось создать FIFO!\n");
    exit(-1);
  }

  if ((file = open(name, O_WRONLY)) < 0) {
    printf("{Ошибка} Не удалось открыть FIFO для записи!\n");
    exit(-1);
  }

  size_t size = write(file, "Это я пишу в файл...", 14);
  if (size != 14) {
    printf("{Ошибка} Не удалось записать все строки в FIFO!\n");
    exit(-1);
  }

  if (close(file) < 0) {
    printf("{Ошибка} НЕ удалось закрыть FIFO!\n");
    exit(-1);
  }

  return 0;
}
