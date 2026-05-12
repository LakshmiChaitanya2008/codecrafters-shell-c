#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);
  while(true) {
    printf("$ ");
    char cmd[100]; 
    scanf("%s", cmd);
    if(strcmp(cmd, "exit") == 0) {
	exit(0);
    }
    printf("%s: command not found\n", cmd);
  }
  return 0;
}
