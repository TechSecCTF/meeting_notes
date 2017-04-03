#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void vuln(char *buf1)
{
  char buf2[100];
  strcpy(buf2, buf1);
}

void shell() {
  system("/bin/sh");
}

int main(int argc, char *argv[])
{
  printf("Try to pop a shell:\n");
  fflush(NULL);
  char buf1[200];
  fgets(buf1, 200, stdin);
  vuln(buf1);
  return 0;
}
