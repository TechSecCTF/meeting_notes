#include <stdio.h>

int main()
{
    int x;
    printf("Guess what number I'm thinking of: ");
    scanf("%d", &x);
    if (x == 83) {
      printf("Right! Bet you can't do it again: ");
      scanf("%d", &x);
      if ((x * 3) == 48) {
        printf("Right again! OK, one last time: ");
        scanf("%d", &x);
        if ((x * x == 121) && (x <= 10)) {
          printf("\x1b[32mCongratulations! You win!\x1b[0m\n");
        } else {
          printf("Nope.\n");
        }
      } else {
        printf("Nope.\n");
      }
    } else {
      printf("Nope.\n");
    }
    return 0;
}
