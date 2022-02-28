#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
  char pathname[] = "tesk-write.c";
  key_t key;
  if ((key = ftok(pathname, 0)) < 0) {
    printf("[Ошибка] Не удалось сгенерировать ключ!\n");
    exit(-1);
  }

  int shmid;
  if ((shmid = shmget(key, 2000*sizeof(char), 0666|IPC_CREAT)) < 0) {
    printf("{Ошибка} Не удалось получить доступ к выделенной памяти!\n");
    exit(-1);
  }

  char *buffer;
  if ((buffer = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
    printf("{Ошибка} Не удалось воспользоваться выделенной памятью!\n");
  }

  int current = 0;
  while(buffer[current] != '\0') {
    printf("%c", buffer[current]);
    ++current;
  }

  if (shmdt(buffer) < 0) {
    printf("{Ошибка} Не удалось отделить память!\n");
    exit(-1);
  }

  if (shmctl(shmid, 0, NULL) < 0) {
    printf("{Ошибка} Не удалось освободить память!\n");
    exit(-1);
  }

  return 0;
}
