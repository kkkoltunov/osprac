#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 0;

void *mythread(void *dummy) {
  pthread_t thid;
  thid = pthread_self();
  counter = counter + 1;

  printf("{поток %u} результат = %d\n", thid, counter);
  return NULL;
}

int main() {
  pthread_t main_thid, thid1, thid2;
  int result;

  result = pthread_create (&thid1, (pthread_attr_t *)NULL, mythread, NULL);

  if (result != 0) {
    printf ("{ошибка} при создании первой нити: %d\n", result);
    exit(-1);
  }

  printf("{поток %u} created\n", thid1);

  result = pthread_create (&thid2, (pthread_attr_t *)NULL, mythread, NULL);

  if (result != 0) {
    printf ("{ошибка} при создании второй никити: %d\n", result);
    exit(-1);
  }

  printf("{поток %u} создан\n", thid2);

  main_thid = pthread_self();
  counter = counter + 1;

  printf("{поток %u} результат = %d\n", main_thid, counter);

  pthread_join(thid1, (void **)NULL);
  pthread_join(thid2, (void **)NULL);

  return 0;
}
