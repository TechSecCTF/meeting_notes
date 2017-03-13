#include <stdio.h>
#include <string.h>


int main(){
    printf("Please enter the password!\n");

    char str1[25];
    scanf("%25s", str1);

    if(!strncmp(str1, "TechSec{w0w_much_str1ngz}", 25)){
      printf("Nice work!\n");
    }
    else{
      printf("Try again!\n");
    }
}
