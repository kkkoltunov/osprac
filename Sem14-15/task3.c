#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

void handler(int nsig) {
  int status;
  pid_t pid = waitpid(-1, &status, WNOHANG);

  while (pid != 0) {
    if (pid < 0) {
      if (errno != 10) {
        printf("Произошла ошибка: %d \n", errno);
      } else {
        printf("Нечего закрывать! \n");
      }

      return;
    } else {
      if ((status & 0xff) == 0) {
        printf("Процесс с id = %d был вызван со статусом: %d \n", pid, status >> 8);
      } else if ((status & 0xff00) == 0) {
        printf("Процесс с id = %d был закрыт со статусом: %d %s \n", pid,
        status &0x7f, (status & 0x80) ? "с файлом" : "без файла");
      }

      pid = waitpid(-1, &status, WNOHANG);
    }
  }
}

int main(void) {
  (void) signal(SIGCHLD, handler);

  pid_t pid;
  for (int i = 0; i < 10; ++i) {
    if ((pid = fork()) < 0) {
      printf("Не удалось форкнуть child 1! \n");
      exit(1);
    } else if (pid == 0) {
      for (int j=1; j < 10000000; ++j);
      exit(200 + i);
    }
  }

  while(true);
  return 0;
}
