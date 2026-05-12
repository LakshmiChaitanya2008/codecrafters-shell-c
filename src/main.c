#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);
  while(true) {
    printf("$ ");
    char cmd[100]; 
    scanf("%s", cmd);
    printf("%s: command not found\n", cmd);
  }
  return 0;
}
