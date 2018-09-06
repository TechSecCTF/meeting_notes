#include <stdio.h>

void secret(char* str) {
  int i = 0;
  while (i < 10) {
    str[i] = 'a' + (25 - (str[i] - 'a'));
    i++;
  }
  return;
}

int main()
{
  char password[10];
  printf("What's the password: ");
  scanf("%10s", password);
  secret(password);
  if (!strcmp(&password, "wzbwivznvi")) {
    printf("\x1b[32mCongratulations! You win!\x1b[0m\n");
  } else {
    printf("Nope.\n");
  }
  return 0;
}
