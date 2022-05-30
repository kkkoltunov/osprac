#include <signal.h>
#include <stdio.h>

void handler(int nsig) {
  if (nsig == 2)
    printf("{CTRL-C} Получен сигнал - %d \n", nsig);
  else if (nsig == 3)
    printf("{CTRL-4} Получен сигнал - %d \n", nsig);
}

int main(void) {
  (void)signal(SIGINT, handler);
  (void)signal(SIGQUIT, handler);

  while(true);
  return 0;
}
