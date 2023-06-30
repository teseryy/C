#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int * arr;
    int length;
    int count;
} dynArray_t;

typedef struct {
  dynArray_t nums;
  char side;
} ram_t;

void removeNL( char str[]){
  size_t len = strlen(str);
  if (len > 1 && str[len-1] == '\n')
    str[len-1] = '\0';
}

void record(ram_t * token, int *num, int *isNeg){
  if ((*token).nums.length == (*token).nums.count) {
    (*token).nums.length *= 2;
    (*token).nums.arr = (int *) realloc((*token).nums.arr, (*token).nums.length * sizeof(int));
  }
  if (*isNeg)
    *num *= (-1);
  (*token).nums.arr[(*token).nums.count] = *num;
  *num = 0;
  *isNeg = 0;
  (*token).nums.count++;
}

int readZ(ram_t ** tokens){//add input in 1 line
  int count_t = -1, length = 0, num = 0, isNeg = 0;
  size_t len;
  char * line=NULL;
  (*tokens) = (ram_t *)malloc(4*sizeof(ram_t));

  while (getline(&line, &len, stdin) >= 0){

    removeNL(line);
    length = strlen(line);

    for(int i=0; i < length; i++) {
      if (isdigit(line[i]))
        num = num * 10 + (int) line[i] - 48;
      else if((int) line[i] == 45)
        isNeg = 1;
      else if ((int) line[i] == 44 || (int) line[i] == 125)
        record(&(*tokens)[count_t], &num, &isNeg);

      if (isupper(line[i])){
        count_t++;
        (*tokens)[count_t].side = line[0];
        (*tokens)[count_t].nums.length = 1;
        (*tokens)[count_t].nums.count = 0;
        (*tokens)[count_t].nums.arr = (int *)malloc((*tokens)[count_t].nums.length * sizeof(int));
      }

    }

    free(line);
    len = 0;
  }
  free(line);
  return count_t;
}

void game(){
  
}

int main( void ){
  ram_t * tokens;

  printf("Zetony:\n");
  readZ(&tokens);

  for (int i=0; i < 4; i++){
      printf("%c ", tokens[i].side);
      for (int j=0; j < tokens[i].nums.count; j++)
        printf("%d ", tokens[i].nums.arr[j]);
      printf("\n");
      free(tokens[i].nums.arr);
  }
  free(tokens);

  return 0;
}
