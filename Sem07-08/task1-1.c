#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
  FILE *f = fopen("test.txt", "r");
  char pathname[] = "tesk-write.c";
  key_t key;
  if ((key = ftok(pathname,0)) < 0) {
    printf("{Ошибка} Не удалось сгенерировать ключ!\n");
    exit(-1);
  }

  int shmid;
  if ((shmid = shmget(key, 2000*sizeof(char), 0666|IPC_CREAT)) < 0) {
    printf("{Ошибка} Не удалось создать общую память!\n");
    exit(-1);
  }

  char *buffer;
  if ((buffer = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
    printf("{Ошибка} Не удалось воспользоваться выделенной памятью!\n");
    exit(-1);
  }

  int current = 0;
  while (!feof(f) & current < 1999) {
    buffer[current] = fgetc(f);
    ++current;
  }
  printf("Это 1 программа!\n");

  if (shmdt(buffer) < 0) {
    printf("{Ошибка} Не удалось отделить память!\n");
    exit(-1);
  }

  fclose(f);
  return 0;
}
