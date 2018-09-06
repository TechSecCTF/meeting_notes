#include <stdio.h>

int do_op(int a, int b, int op) {
  switch(op) {
    case 0:
      return a + b;
    case 1:
      return a - b;
    case 2:
      return a * b;
  }
  return 0;
}

int generate(int a, int b, int c, int d) {
  b = do_op(a, b, rand() % 3);
  c = do_op(b, c, rand() % 3);
  d = do_op(c, d, rand() % 3);
  return d;
}

int verify(int a, int b, int c, int d, int e, int op1, int op2, int op3) {
  b = do_op(a, b, op1);
  c = do_op(b, c, op2);
  d = do_op(c, d, op3);
  return d == e;
}

int main()
{
  srand(time(NULL));
  int MAX = 50;
  int i;
  for (i = 0; i < 10; i++) {
    int a = rand() % MAX;
    int b = rand() % MAX;
    int c = rand() % MAX;
    int d = rand() % MAX;
    int e = generate(a, b, c, d);
    printf("%d %d %d %d %d\n", a, b, c, d, e);
    int op1, op2, op3;
    scanf("%d %d %d", &op1, &op2, &op3);
    if (!verify(a, b, c, d, e, op1, op2, op3)) {
      printf("Nope!\n");
      return 0;
    }
    printf("Good!\n");
  }
  printf("\x1b[32mCongratulations! You win!\x1b[0m\n");
  return 0;
}
