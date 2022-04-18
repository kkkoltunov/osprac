#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>

// идем в таком порядке:
// 1.родитель
// пишем
// A(S,2)
// Z(S)
// читаем
// 2.ребенок
// D(S,1)
// читаем
// пишем
// D(S,1)

int main() {
  int fd[2];
  char pathname[] = "3.c";

  int N;
  scanf("%d", &N);

  if (pipe(fd) < 0) {
    printf("{ошибка} не удалось открыть pipe\n");
    exit(-1);
  }

  key_t key;
  if ((key = ftok(pathname,0)) < 0) {
    printf("{ошибка} не удалось сгенерировать ключ\n");
    exit(-1);
  }

  int semid;
  if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
    printf("{ошибка} не удалось получить семафоры\n");
    exit(-1);
  }

  int result = fork();
  if (result < 0) {
    printf("{ошибка} не удалось форкнуть ребенка\n");
    exit(-1);
  }

  size_t size;
  char  message[16];
  struct sembuf mybuf;
  for (int i = 0; i < N; ++i) {
    if (result > 0) { // родитель
      size = write(fd[1], "Это пишет родитель!", 16);
      if (size != 16) {
        printf("{ошибка родитель} не удалось записать все строки в pipe\n");
        exit(-1);
      }

      mybuf.sem_num = 0;
      mybuf.sem_op = 2;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("{ошибка родитель} не удалось получить состояние\n");
        exit(-1);
      }

      mybuf.sem_num = 0;
      mybuf.sem_op = 0;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("{ошибка родитель} не удалось получить состояние\n");
        exit(-1);
      }

      size = read(fd[0], message, 16);
      if (size != 16) {
        printf("{ошибка родитель} не удалось прочитать строку из pipe\n");
        exit(-1);
      }

      printf("[родитель %d] прочитаные строки из pipe: %s\n", i, message);
    } else { // ребенок
      mybuf.sem_num = 0;
      mybuf.sem_op = -1;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("{ошибка родитель} не удалось получить состояние\n");
        exit(-1);
      }

      size = read(fd[0], message, 16);
      if (size != 16) {
        printf("{ошибка ребенок} не удалось прочитать из pipe\n");
        exit(-1);
      }

      printf("[ребенок %d] прочитано из pipe: %s\n", i, message);

      size = write(fd[1], "Это пишет ребенок!", 16);
      if (size != 16) {
        printf("{ошибка ребенок} не удалось записать все в pipe\n");
        exit(-1);
      }

      mybuf.sem_num = 0;
      mybuf.sem_op = -1;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("{ошибка родитель} не удалось получить состояние\n");
        exit(-1);
      }
    }
  }

  if (close(fd[0]) < 0) {
    printf("{ошибка} не удалось закрыть поток чтения pipe\n");
    exit(-1);
  }

  if (close(fd[1]) < 0) {
    printf("{ошибка} не удалось закрыть поток записи pipe\n");
    exit(-1);
  }

  return 0;
}
