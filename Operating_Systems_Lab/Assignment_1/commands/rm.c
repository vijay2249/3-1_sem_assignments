#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
  printf("After completion the mentioned file will be deleted\n");
  int count;
  for(count=1;count<argc;count++){
    printf("The mentioned file '%s' will be deleted\n", argv[count]);
    remove(argv[count]);
  }
  return 0;
}