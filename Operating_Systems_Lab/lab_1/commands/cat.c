#include <stdio.h> //Used for basic input/output stream
#include <string.h>
#include <stdlib.h>
#include <errno.h> //For EXIT codes and error handling
 
int main(int argc, char *argv[]) {
  FILE *file;
  int chr, count;
  for(count = 1; count < argc; count++) {
    if((file = fopen(argv[count], "r")) == NULL) {
      fprintf(stderr, "%s: %s : %s\n", argv[0], argv[count], strerror(errno));
      continue;
    }
    while((chr = getc(file)) != EOF)
      fprintf(stdout, "%c", chr);
    fclose(file);
  }
  exit(0);
}
