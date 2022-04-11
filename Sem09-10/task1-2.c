#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
  char pathname[]="09-1-2.c";

  key_t key;
  if ((key = ftok(pathname,0)) < 0) {
    printf("{Ошибка 09-1-2.c} не удалось сгенерировать ключ!\n");
    exit(-1);
  }

  int semid;
  if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
    printf("{Ошибка 09-1-2.c} не удалось сгенерировать массив симофоров\n");
    exit(-1);
  }

  struct sembuf mybuf;
  mybuf.sem_num = 0;
  mybuf.sem_op  = 1;
  mybuf.sem_flg = 0;

  if (semop(semid, &mybuf, 1) < 0) {
    printf("{09-1-2.c} не удалось добавить семафорn");
    exit(-1);
  }

  printf("{09-1-2.c} условие выполнено\n");
  return 0;
}
