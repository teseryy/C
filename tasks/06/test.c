#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

int isEmpty( char * str){
	int len = strlen(str);
	
	for (int i=0; i < len; i++){
		if (str[i] != ' ' || str[i] != '\t')
			return 0;
	}
	printf("1\n");
	return 1;
}

int main( void ){
	int length, res=0;
	size_t len;
	char * str=NULL;
	getline(&str, &len, stdin);
	str = strtok(str, "\n");
	
	for (int i=1; i < strlen(str); i++){
		//printf("n=%d\n", 
		res = res*10 + (int)str[i] - 48;
	}
	printf("%d\n", res);
	
	free(str);
	return 0;
}
