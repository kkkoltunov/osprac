#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct mymsgbuf {
    long mtype;
    struct{
      int iinfo;
    }info;
  } mybuf;

  char pathname[] = "ex2a.c";
  key_t key;
  if ((key = ftok(pathname, 0)) < 0) {
    printf("{ошибка} не удалось сгенерировать ключ\n");
    exit(-1);
  }

  nt msqid;
  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("{ошибка} не удалось получить msqid\n");
    exit(-1);
  }

  int len, maxlen;
  for (int i = 1; i <= 5; ++i) {
    mybuf.mtype = 1;
    mybuf.info.iinfo = 123;
    len = sizeof(mybuf.info);

    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
      printf("{ошибка} не удалось добавить сообщение в очередь\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
      exit(-1);
    }
  }

  for (int i = 1; i <= 5; ++i) {
    maxlen = sizeof(mybuf.info);

    if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0) < 0) {
      printf("{ошибка} не удалось получить сообщение из очереди\n");
      exit(-1);
    }

    printf("{результат} message type = %ld, iinfo = %i\n", mybuf.mtype, mybuf.info.iinfo);
  }

  msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);

  return 0;
}
