#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct mymsgbuf {
    long mtype;
    struct {
      int iinfo;
      float finfo;
    } info;
  } mybuf;

  key_t key;
  char pathname[] = "ex1a.c";
  if ((key = ftok(pathname, 0)) < 0) {
    printf("{ошибка} не удалось сгенерировать ключ\n");
    exit(-1);
  }

  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("{ошибка} не удалось получить msqid\n");
    exit(-1);
  }

  int len;
  int msqid;
  for (int i = 1; i <= 5; ++i) {
    mybuf.mtype = 1;
    mybuf.info.iinfo = 123;
    mybuf.info.finfo = 1.23;
    len = sizeof(mybuf.info);

    if (msgsnd(msqid, &mybuf, len, 0) < 0) {
      printf("{ошибка} не удалось добавить сообщение в очередь\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
      exit(-1);
    }
  }

  mybuf.mtype = 255;
  len = 0;
  if (msgsnd(msqid, &mybuf, len, 0) < 0) {
    printf("{ошибка} не удалось добавить сообщение в очередь\n");
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    exit(-1);
  }

  return 0;
}
