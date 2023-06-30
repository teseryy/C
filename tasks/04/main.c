#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 2000

int compare(const int * i, const int * j){
	int a = *i, b = *j;
	return ( a > b ) - ( b > a );
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
  int count_nums, count_sums, length, summ, num, res, comb, count;
  int *nums=NULL, *sums=NULL;
  length = 4;
  count_nums = 0;
  count_sums = 0;
  comb = 0;
  
  nums = (int*)malloc(length * sizeof(int));

  printf("Posloupnost:\n");

  res = scanf("%d", &num);
  if (res != 1){
    printf("Nespravny vstup.\n");
    free(nums);
    free(sums);
    return 1;
  }

  while (res != EOF){
    if (res != 1 || count_nums >= MAX_LEN){
      printf("Nespravny vstup.\n");
      free(nums);
      free(sums);
      return 1;
    }
    if (count_nums == length){
      length *= 2;
      nums = (int*)realloc(nums, length * sizeof(int));
    }
    nums[count_nums] = num;
    count_nums++;
    res = scanf("%d", &num);
  }  
  
  sums = (int*)malloc(length * sizeof(int));
  for (int i=0; i < (count_nums - 1); i++){
    summ = nums[i];
    for (int j=i+1; j < count_nums; j++){
      if (count_sums == length){
        length *= 2;
        sums = (int*)realloc(sums, length * sizeof(int));
      }
      
      summ += nums[j];
      sums[count_sums] = summ;
      count_sums++;
    }
  }
  
  qsort(sums, count_sums, sizeof(int), (int (*) (const void *, const void *)) compare);
  
  count = 1;
  for (int i=0; i < (count_sums-1); i++){
    if (sums[i] == sums[i+1])
      count++;
    else
      if (count != 1){
      	comb += c_comb(count);
      	//printf("%d %d\n", count, comb);
      	count = 1;
      }
  } 
  
  printf("Pocet dvojic: %d\n", comb);
  /*for(int i=0; i< count_sums; i++) 
    printf("%d ", sums[i]);

  printf("\n");
  */

	free(nums);
  free(sums);
  
  return 0;
}

