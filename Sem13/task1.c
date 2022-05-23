#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *fp;

  char name[] = "temp/a";
  if ((fp = fopen(name, "a")) == NULL) {
    printf("ERROR\n");
    return 0;
  }
  
  char link_name[] = "temp/b";
  symlink(name, link_name);

  FILE *new_fp;
  int depth = 0;
  while ((new_fp = fopen(link_name, "r")) != NULL) {
    ++depth;

    strcpy(name, link_name);
    link_name[5] = 'a' + 1 + depth;
    symlink(name, link_name);
    fclose(new_fp);
  }

  printf("%d\n", depth);
  fclose(fp);

  return 0;
}
