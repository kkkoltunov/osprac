#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    printf("Hello, your id = %d\n" + getuid());
    printf("group id = %d\n" + getgid());
return 0;
}
