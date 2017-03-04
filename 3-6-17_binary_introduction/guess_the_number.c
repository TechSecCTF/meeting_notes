#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_number() {
    srandom(time(NULL));
    return random() % 20 + 1;
}

int guess(int target) {
    int tries = 0;
    int guess;

    while (1) {
        tries++;
        scanf("%d", &guess);

        if (guess == 31337) {
            printf("Well done.\n");
            return -1;
        }

        if (target < guess)
            printf("Too high.\n");
        else if (target > guess)
            printf("Too low.\n");
        else
            return tries;
    }
    
}

int main(void) {
    printf("I'm thinking of a number between 1 and 20.\n");
    printf("Can you guess what it is?\n");

    int target = random_number();
    int tries = guess(target);

    if (tries > 5)
        printf("You're slow.\n");
    else if (tries > 4)
        printf("Not bad.\n");
    else
        printf("How did you do that?\n");

    return 0;
}
