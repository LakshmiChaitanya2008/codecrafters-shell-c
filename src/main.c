#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

bool isBuiltIn(char str[]) {
  char cmds[][100] = {"exit", "echo", "type"};

  for(int i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++) {
     if(strcmp(str, cmds[i]) == 0) {
     	return true;
     }
  }
  return false;
}

char* locateExecutable(char cmd[]) {
  char *path_env = getenv("PATH");
  static char path[4096];

  char path_copy[4096];
  strcpy(path_copy, path_env);

  char *dir = strtok(path_copy, ":");

  while(dir != NULL) {
    sprintf(path, "%s/%s", dir, cmd);

    if(access(path, X_OK) == 0) {
	return path;
    }

    dir = strtok(NULL, ":");
  }
  
  return NULL;
}

void runExecutable(char cmd[]) {
  char *args[100];

  char *token = strtok(cmd, " ");
  int i = 0;

  while(token != NULL) {
    args[i++] = token;
    token = strtok(NULL, " ");
  }

  args[i] = NULL;

  pid_t pid = fork();

  if(pid == 0) {
    execvp(args[0], args);

    printf("%s: command not found\n", args[0]);
    exit(1);
  } else {
    wait(NULL);
  }

}

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);
  while(true) {
    printf("$ ");

    char cmd[100];

    if(fgets(cmd, 100, stdin) == NULL) {
	break;
    }
    cmd[strcspn(cmd, "\n")] = '\0';

    if(strcmp(cmd, "exit") == 0) {
	exit(0);
    } else if(strncmp(cmd, "echo ", 5) == 0) {
	printf("%s\n", cmd + 5);
    } else if(strncmp(cmd, "type ", 5) == 0) {
	char *arg = cmd + 5;
	if(isBuiltIn(arg)) {
	   printf("%s is a shell builtin\n", arg);
	} else {
           char* path = locateExecutable(arg);

	   if(path != NULL) {
	     printf("%s is %s\n", arg, path);
	   } else {
	     printf("%s: not found\n", arg);
	   }
	}
    } else {
        runExecutable(cmd);
    }
  }
  return 0;
}
