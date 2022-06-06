#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sendpid;
int number = 2147483647;

int step = 0;
void getFirst() {
  number = number ^ (1 << step);
  ++step;

  if (step == 32) {
    printf("{получатель} число: %d \n", number);
    exit(0);
  } else {
    printf("{получатель} %d бит: %d \n", step, 0);
    kill(sendpid, SIGUSR1);
  }
}

void getSecond() {
  ++step;

  if (step == 32) {
    printf("{получатель} число: %d \n", number);
    exit(0);
  } else {
    printf("{получатель} %d бит: %d \n", step, 1);
    kill(sendpid, SIGUSR1);
  }
}

int main(void) {
  (void)signal(SIGUSR1, getFirst);
  (void)signal(SIGUSR2, getSecond);

  printf("{получатель} PID: %d \n", getpid());

  printf("{получатель} введите PID отправителя: ");
  scanf("%d", &sendpid);

  while(true) {};
}
