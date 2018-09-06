#include<stdio.h>
#include <stdlib.h>
#include<signal.h>
#include<unistd.h>

void sig_handler(int signo)
{
  FILE* f;	
  f = fopen ("flag.txt", "r");
	char flag[100];
	fgets(flag, 30, f);
	printf("%s", flag);
	exit(0);
}

int main(void)
{
  signal(SIGSEGV, sig_handler);
	printf("Make me crash and I'll give you the flag:\n");
  fflush(NULL);
	char buf[50];
	scanf("%s", buf);
  return 0;
}
