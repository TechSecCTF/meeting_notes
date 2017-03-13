#include <stdio.h>

double func(double a, double b, double c, double d, double e, double f, double g, double h) {
    return a + b + c + d + e + f + g + h;
}

int main(void) {
    double a=1, b=2, c=3, d=4, e=5, f=6, g=7, h=8;
    double val = func(a,b,c,d,e,f,g,h);
    printf("%f\n", val);
}
