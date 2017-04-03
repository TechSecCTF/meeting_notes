#include <stdio.h>

struct my_struct {
  char buf[64];
  int canary;
};

int main() {
  FILE* f;
  f = fopen ("flag.txt", "r");
  char flag[100];
  fgets(flag, 30, f);


  struct my_struct m;
  m.canary = 0;
  printf("Show me what you've got:\n");
  fflush(NULL);
  scanf("%100s", m.buf);

  if (m.canary == 31337) {
    printf("%s", flag);
  } else {
    printf("Nice try.\n");
  }
  return 0;
}
