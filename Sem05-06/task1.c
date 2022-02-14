#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int     fd;
  size_t  size;
  char    restring[14];

  (void)umask(0);

  if ((fd = open("myfile", O_RDONLY, 0666)) < 0) {
    printf("Не удалось открыть файл!\n");
    exit(-1);
  }

  size = read(fd, restring, 14);

  if (size != 14) {
    printf("Не удалось прочитать все строки!\n");
    exit(-1);
  }

  printf("Из файла: %s\n", restring);

  if (close(fd) < 0) {
    printf("не удалось закрыть файл!\n");
  }

  return 0;
}
