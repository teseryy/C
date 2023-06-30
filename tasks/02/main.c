#include <stdio.h>
#include <math.h>

int IsPrime( int x ){
  if ((x % 2 == 0 && x != 2) || x == 1)
    return 0;
  else if(x == 3 || x == 2)
    return 1;
  else{
    for (int i=3; i < (sqrt(x)+1); i+=2){
      if (x % i == 0)
        return 0;
    }
  }

  return 1;
}


int main( void ){
  int lo, hi, sum, count, j, end;
  char typ;

  printf("Intervaly:\n");
  
  while(scanf(" %c %d %d", &typ, &lo, &hi) != EOF){

    if (lo > hi || lo < 1 || (typ != '?' && typ != '#')){
      printf("Nespravny vstup.\n");
      return 1;
    }
    
    count = 0;

    for (int i=lo; i<=hi; i++){
      sum = 0;
      
      end = sqrt(i) + 1;
      for (j=2; j < end; j++){
        if (i % j == 0){
          if (j != i/j)
            sum += j + (i/j);
          else
            sum += j;
        }
      }
      sum += 1; 

      if (IsPrime(sum)){
        count++;
        if (typ == '?')
          printf("%d\n", i);
      } 
    }
    printf("Celkem: %d\n", count);
  }
  
  return 0;
}
