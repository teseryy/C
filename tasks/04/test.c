#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 2000

int compare(const void *i, const void *j){
  return *(int *)i - *(int *)j;
}

int c_comb(int n){
  int m = 2;
  int k = n - m;
  if (m > k)
    m = k;
  if (!m)
    return 1;
  int akk = k = n - m + 1;
  k++;
  for (int i = 2; i <= m; i++, k++)
    akk = akk / i * k + akk % i * k / i;
  return akk;
}

int main( void ){
  printf ("%d\n", c_comb(4));
  
  return 0;
}
