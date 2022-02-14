#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int     fd1[2], fd2[2], result;

  size_t size1, size2;
  char  resstring1[27], resstring2[26];

  if (pipe(fd1) < 0) {
    printf("Не удалось открыть первый pipe\n");
    exit(-1);
  }

  if (pipe(fd2) < 0) {
    printf("Не удалсь открыть второй pipe\n");
    exit(-1);
  }

  result = fork();

  if (result < 0) {
    printf("Не удалось форкнуть первого ребенка\n");
    exit(-1);
  } else if (result > 0) {

   /* Parent process */

    if (close(fd1[0]) < 0) {
      printf("{parent} Не удалось закрыть первый pipe\n"); exit(-1);
    }

    size1 = write(fd1[1], "это родитель", 27);

    if (size1 != 27) {
      printf("Не удалось записать все строки в pipe\n");
      exit(-1);
    }

    if (close(fd1[1]) < 0) {
      printf("[parent] Can\'t close writing side of first pipe\n"); exit(-1);
    }

    if (close(fd2[1]) < 0) {
      printf("parent} Не удалось закрыть второй pipe\n"); exit(-1);
    }

    size2 = read(fd2[0], resstring2, 26);

    if (size2 < 0) {
      printf("Не удалось прочитать из второго pipe\n");
      exit(-1);
    }

    printf("ПРодитель:  %s\n", resstring2);

    if (close(fd2[0]) < 0) {
      printf("{parent} Не удалось закрыть читающий второй pipe\n"); exit(-1);
    }

  } else {

    /* Child process */

    if (close(fd1[1]) < 0) {
      printf("{child} Не удалось закрыть пишущий второй pipe\n"); exit(-1);
    }

    size1 = read(fd1[0], resstring1, 27);

    if (size1 < 0) {
      printf("Не удалось прочитать из первого pipe\n");
      exit(-1);
    }

    printf("Ребенок:  %s\n", resstring1);

    if (close(fd1[0]) < 0) {
      printf("{child} Не удалось закрыть читающий первый pipe\n"); exit(-1);
    }

    if (close(fd2[0]) < 0) {
      printf("{child} Не удалось закрыть читающий второй pipe\n"); exit(-1);
    }

    size2 = write(fd2[1], "это ребенок!", 26);

    if (size2 != 26) {
      printf("Не удалось прочитать все строки из второго pipe\n");
      exit(-1);
    }

    if (close(fd2[1]) < 0) {
      printf("{child} Не удалось закрыть читающий второй pipe\n"); exit(-1);
    }
  }

  return 0;
}
