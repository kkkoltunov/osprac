#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int received = 1;
void waiting() {
  received = 1;
}

int main(void) {
  (void)signal(SIGUSR1, waiting);

  printf("{отправитель} PID: %d \n", getpid());

  printf("{отправитель} укжаите PID получателя: ");
  int recpid;
  scanf("%d", &recpid);

  printf("{отправитель} введите число: ");
  int number;
  scanf("%d", &number);

  for (int i = 0; i < 32; ++i) {
    if ((number & (1 << i)) == 0) {
      kill(recpid, SIGUSR1);
    } else {
      kill(recpid, SIGUSR2);
    }

    received = 0;
    while (i != 31 && received == 0) {}
  }

  printf("{отправитель} число: %d \n", number);
  return 0;
}
