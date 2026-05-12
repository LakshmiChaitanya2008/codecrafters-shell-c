#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);
  while(true) {
    printf("$ ");

    char cmd[100];

    fgets(cmd, 100, stdin);
    cmd[strlen(cmd) - 1] = '\0';

    if(strcmp(cmd, "exit") == 0) {
	exit(0);
    } else if(strncmp(cmd, "echo ", 5) == 0) {
	printf("%s\n", cmd + 5);
    } else {
        printf("%s: command not found\n", cmd);
    }
  }
  return 0;
}
