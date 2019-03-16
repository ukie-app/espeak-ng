#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	printf(">preprocessText\n");
	printf("src before:%s\n", src);
	// Create input file
	FILE *inputFile = fopen("/tmp/mishkal_input", "w");
	int results = fputs(src, inputFile);
	if (results == EOF)
		printf(stderr, "Error writing mishkal input file\n");
	fclose(inputFile);
	// Generate mishkal output file
	system(
			"/home/valdis/code/mishkal/bin/mishkal-console.py -s -f /tmp/mishkal_input > /tmp/mishkal_output");
	// Read mishkal output into buffer
	FILE * outputFile = fopen("/tmp/mishkal_output", "r");
	if (outputFile) {
		// Get size of file
		fseek(outputFile, 0L, SEEK_END);
		int size = ftell(outputFile);
		rewind(outputFile);
		printf("size:%d\n",size);
		// Read file into buffer
		fread(src, 1, size, outputFile); // FIXME this fails tests/ssml-fuzzer.check test, because mishkal output is longer than input
	} else
		printf(stderr, "Error reading mishkal output file");
	printf("src after:%s\n", src);
	fclose(outputFile);
	printf("<preprocessText\n");
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

