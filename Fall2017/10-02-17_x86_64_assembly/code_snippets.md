# Code Snippets

## registers, local variables

```C
int main()
{
    int a, b;
    a = 2;
    b = a + 7;
}
```

## return values

```C
int getRandomNumber()
{
    return 4; // chosen by a fair dice roll.
              // guaranteed to be random.
}
```

## functions, arguments

```C
int foo(int a, int b)
{
    return a * b;
}

int main()
{
    int a, b, c;
    a = 2;
    b = a + 7;
    c = foo(a, b);
}
```


## conditionals, branching
```C
#include <stdio.h>

int main()
{
    int a = 3;
    if (a < 10) {
        printf("%d is small", a);
    } else {
        printf("%d is big", a);
    }
}
```
