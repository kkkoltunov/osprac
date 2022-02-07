#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[], char *envp[]) {
	pid_t process_id = fork();

	if (process_id < 0) {
		printf("Error has found! (creating process)\n");
		exit(-1);
	} else if (process_id == 0) {
		printf("It's child! Call cat for task4.c\n");
		(void) execle("/bin/cat", "/bin/cat", "task4.c", 0, envp);
		printf("Error has found! (calling program)\n");
		exit(-1);
	} else {
		printf("It's parent!\n");
	}
	return 0;
}
