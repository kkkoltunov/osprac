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

  int msqid;
  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("{ошибка} не удалось получить msqid\n");
    exit(-1);
  }

  int len, maxlen;
  while (1) {
    maxlen = sizeof(mybuf.info);

    if (len = msgrcv(msqid, &mybuf, maxlen, 0, 0) < 0) {
      printf("{ошибка} не удалось получить сообщение из очереди\n");
      exit(-1);
    }

    if (mybuf.mtype == 255) {
      msgctl(msqid, IPC_RMID, NULL);
      exit(0);
    }

    printf("{результат} message type = %ld, iinfo = %i, finfo = %f\n", mybuf.mtype, mybuf.info.iinfo, mybuf.info.finfo);
  }

  return 0;
}
