#include <stdio.h>
#include <string.h>


  char str1[31] = {'U', 'f', 'e', 'k', 'X', 'm', 'p', '\x90', '\x99', '\x9f', '\x89', '\xef', 'M', '\xda', '\xc8', 'P', '\xae', 'w', '\xbe', '\xa2', '!', '\x95', '"', '\x82', 'A', '\x9f', '\xa3', '\xd6', '\x18', '\x91', 'Z'};

void secret_transform(char *str){
  int a = 0;
  int b = 1;
  int i;
  for (i = 0; i < 31; i++){
    str[i] = str[i] + b;
    b = a+b;
    a = b-a;
  }
  return;
}

int main(){

  char str2[31];

  printf("Please enter the password\n");
  scanf("%31s", str2);

  secret_transform(str2);

  if(!strncmp(str1, str2, 31)){
      printf("You're getting good at this!\n");
  } else{
    printf("Try again... You can do it!\n");
  }
}
