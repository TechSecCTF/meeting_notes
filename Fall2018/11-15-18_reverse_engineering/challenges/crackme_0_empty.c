#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECSIZE 16
unsigned char secret[] = SECRET;
unsigned char buffer[SECSIZE];
unsigned char hex[] = "0123456789abcdef";

void decrypt() {
  //this is for you to find out
}

void wrong(char* input) {
  printf("%s is wrong!\n",input);
  exit(1);
}

//converts the string "input" from a hex input into
//a raw binary string, which is placed in buffer
//YOU DO NOT NEED TO REVERSE THIS
int fromhex(char* input) {
  int len = strlen(input);
  //can't decode hex string with odd number of characters
  if (len&1) {
    return 1;
  }
  //make sure len/2 is the size we are looking for
  if (len>>1 != SECSIZE) {
    return 2;
  }

  int i,hi,lo;
  for (i = 0; i < len; i+=2) {
    hi = (int)(strchr(hex,input[i]) - hex);
    lo = (int)(strchr(hex,input[i+1]) - hex);
    //don't want to get an invalid character
    if ((hi > 0xf) || (lo > 0xf) || (hi < 0) || (lo < 0)) {
      return 4;
    }
    buffer[i>>1] = hi<<4 | lo;
  }
  return 0;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    puts("You must provide a serial number!");
    return -1;
  }

  if(fromhex(argv[1])) {
    wrong(argv[1]);
  }
  decrypt();
  if (!memcmp(buffer,secret,SECSIZE)) {
    printf("That is correct!\n");
  }
  else {
    wrong(argv[1]);
  }
  return 0;
  
}
