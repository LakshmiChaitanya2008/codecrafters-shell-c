#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isBuiltIn(char str[]) {
  char cmds[][100] = {"exit", "echo", "type"};

  for(int i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++) {
     if(strcmp(str, cmds[i]) == 0) {
     	return true;
     }
  }
  return false;
}

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
    } else if(strncmp(cmd, "type ", 5) == 0) {
	char *arg = cmd + 5;
	if(isBuiltIn(arg)) {
	   printf("%s is a shell builtin\n", arg);
	} else {
          printf("%s: not found\n", arg);
	}
    } else {
        printf("%s: command not found\n", cmd);
    }
  }
  return 0;
}
