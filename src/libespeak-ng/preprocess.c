#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef N_TR_SOURCE
#define N_TR_SOURCE 800
#endif

/*- This function provides integration with external tools
 * Currently uses system call use GNU tools echo and tr to change "a" into "e"
 * Which writes output in file, which is read back into passed buffer
 *
 * This file can be compiled separately from espeak-ng with command:
 * gcc -DSTANDALONE -o preprocess.o preprocess.c
 *
 * and then executed as stand alone executable with
 * ./preprocess.o "passed arguments"
 */
void preprocessText(char *src) {
    printf("preprocessText>\n");
	char temp[N_TR_SOURCE + 40] = {0};
	char dest[N_TR_SOURCE + 40] = {0};
	printf("src: %s\n", src);
	strcat(temp,"echo \"");
	strcat(temp, src);
	strcat(temp, "\"|tr \"a\" \"e\" > /tmp/test_file");
	system(temp);
	printf("preprocess commmand:%s\n", temp);
	FILE * file;
	file = fopen("/tmp/test_file", "r");
	int c;
	if (file)
		fgets(dest,N_TR_SOURCE,file);
	printf("dest:%s\n",dest);
	strcpy(src,dest);
	fclose(file);
    printf("preprocessText.\n");
}

/*
 * This function is used for testing as stand-alone executable
 */
#ifdef STANDALONE
int main(int argc, char **argv) {
	for(int i=1; i<argc; i++) {
	printf("in %d:%s\n", i, argv[i]);
	preprocessText(argv[i]);
	printf("out %d:%s\n", i, argv[i]);
	}
}
#endif

