#include <stdio.h>
#include <stdlib.h>

/* This function provides integration with external tools
 * Currently uses system call use GNU tools echo and tr to change "a" into "e"
 * Which writes output in file, which is read back into passed buffer
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
