#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
	for(int i = 0; i < argc; ++i) {
		printf("argv: %s\n", argv[i]);
	}

	int i = 0;
	while(envp[i] != 0) {
		printf("envp: %s\n", envp[i]);
		++i;
	}
	
	return 0;
}
