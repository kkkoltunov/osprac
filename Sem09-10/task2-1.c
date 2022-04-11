#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/sem.h>

int main() {
  int new = 1;
  long i;
  char pathname[] = "09-2-1.c";

  key_t key;
  if ((key = ftok(pathname],0)) < 0) {
    printf("{ошибка 09-2-1.c} не удалось сгенерировать ключ!\n");
    exit(-1);
  }

  int semid;
  int shmid;
  if ((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("{ошибка 09-2-1.c} не удалось выделить память!\n");
      exit(-1);
    } else {
      if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
        printf("{ошибка 09-2-1.c} не удалось найти выделенную память!\n");
        exit(-1);
      }
      new = 0;
    }
  }

int *array;
  if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
    printf("{ошибка 09-2-1.c} не удалось воспользоваться памятью!\n");
    exit(-1);
  }

  if ((semid = semget(key, 1, 0666)) < 0) {
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
      printf("{ошибка 09-2-1.c} не удалось создать массив симофоров!\n");
      exit(-1);
    }

    struct sembuf mybuf;
    mybuf.sem_num = 0;
    mybuf.sem_op = 1;
    mybuf.sem_flg = 0;
    if (semop([semid, &mybuf, 1) < 0) {
      printf("{ошибка 09-2-1.c} не удалось выполнить условие!\n");
      exit(-1);
    }
  }

  if (new) {
    array[0] =  1;
    array[1] =  0;
    array[2] =  1;

    printf("{09-2-1.c} программа 1 создана %d раз, программа 2 - %d раз, всего - %d раз\n",
        array[0], array[1], array[2]);
  } else {
    mybuf.sem_num = 0;
    mybuf.sem_op = -1;
    mybuf.sem_flg = 0;

    if (semop(semid, &mybuf, 1) < 0) {
      printf("{ошибка 09-2-1.c} не удалось выполнить условие!\n");
      exit(-1);
    }

    array[0] += 1;
    for(i=0; i<2000000000L; i++);
    array[2] += 1;

    printf("{09-2-1.c} программа 1 создана %d раз, программа 2 - %d раз, всего - %d раз\n",
        array[0], array[1], array[2]);

    mybuf.sem_num = 0;
    mybuf.sem_op = 1;
    mybuf.sem_flg = 0;

    if (semop(semid, &mybuf, 1) < 0) {
      printf("{ошибка 09-2-1.c} не удалось выполнить условие!\n");
      exit(-1);
    }
  }

  if (shmdt(array) < 0) {
    printf("{ошибка 09-2-1.c} не удалось получить доступ к памяти!\n");
    exit(-1);
  }

  return 0;
}
