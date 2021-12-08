// // wc command using c
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

// int main(int argc, char** argv){
//   int bytes = 0;
//   int words = 0;
//   int newLine = 0;
//   char buffer[1];
//   enum states { WHITESPACE, WORD };
//   int state = WHITESPACE;
//   if(argc != 2)printf( "Help: %s filename", argv[0]);
//   else{
//     FILE *file = fopen( argv[1], "r");
//     if(file == 0)printf("can not find :%s\n",argv[1]);
//     else{
//       char *thefile = argv[1];
//       char last = ' ';
//       while (read(fileno(file),buffer,1) ==1 ){
//         bytes++;
//         if ( buffer[0]== ' ' || buffer[0] == '\t') state = WHITESPACE;
//         else if (buffer[0]=='\n'){
//           newLine++;
//           state = WHITESPACE;
//         }
//         else{
//           if (state == WHITESPACE) words++;
//           state = WORD;
//         }
//         last = buffer[0];
//       }
//       printf("New Lines: %d, words: %d, bytes: %d, fileName: %s\n",newLine,words,bytes,thefile);
//    }
//  }
//  return 0;
// }


/*----------- ls command in c -----------*/
#include <stdio.h> //Used for basic input/output stream
#include <dirent.h> //Used for handling directory files
#include <errno.h> //For EXIT codes and error handling
#include <stdlib.h>

void _ls(const char *dir,int op_a,int op_l){
	//Here we will list the directory
	struct dirent *d;
	DIR *dh = opendir(dir);
	if (!dh){
		if (errno = ENOENT){
			perror("Directory doesn't exist"); //If the directory is not found
		}
		else{
			perror("Unable to read directory"); //If the directory is not readable then throw error and exit
		}
		exit(EXIT_FAILURE);
	}
	//While the next entry is not readable we will print directory files
	while ((d = readdir(dh)) != NULL){
		//If hidden files are found we continue
		if (!op_a && d->d_name[0] == '.')
			continue;
		printf("%s  ", d->d_name);
		if(op_l) printf("\n");
	}
	if(!op_l)
	printf("\n");
}

int main(int argc, const char *argv[]){
	if (argc == 1){
		_ls(".",0,0);
	}
	else if (argc == 2){
		if (argv[1][0] == '-'){
			//Checking if option is passed
			//Options supporting: a, l
			int op_a = 0, op_l = 0;
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == 'l') op_l = 1;
				else{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			_ls(".",op_a,op_l);
		}
	}
	return 0;
// }


/*------------ cat command in c ------------*/
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <errno.h>
 
// int main(int argc, char *argv[]) {
//   FILE *file;
//   int chr, count;
//   for(count = 1; count < argc; count++) {
//     if((file = fopen(argv[count], "r")) == NULL) {
//       fprintf(stderr, "%s: %s : %s\n", argv[0], argv[count], strerror(errno));
//       continue;
//     }
//     while((chr = getc(file)) != EOF)
//       fprintf(stdout, "%c", chr);
//     fclose(file);
//   }
//   exit(0);
// }