#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int * arr;
    int length;
    int count;
} dynArray_t;

typedef struct {
    int a;
    int b;
} count_t;

int max( int a, int b ){
  if (a > b)
    return a;
  else
    return b;
}

int min( int a, int b ){
  if (a < b)
    return a;
  else
    return b;
}

void input(dynArray_t * arr){
  int n, num;

  (*arr).length = 1;
  (*arr).count = 0;

  scanf("%d", &n);
  (*arr).arr =(int *)malloc((*arr).length* sizeof(int));

  for (int i = 0; i < n; i++){
    if((*arr).length == (*arr).count){
      (*arr).length *= 2;
      (*arr).arr = (int*)realloc((*arr).arr, (*arr).length * sizeof(int));
    }
    scanf("%d", &num);
    (*arr).arr[i] = num;
    (*arr).count++;
  }

  for (int i = 0; i <((n+1)/2); i++){
    int tmp = 0;
    tmp = (*arr).arr[i];
    (*arr).arr[i] = (*arr).arr[n-i-1];
    (*arr).arr[n-i-1] = tmp;
  }
}

dynArray_t delLE( dynArray_t arr){
  dynArray_t newArr;
  newArr.length = arr.length;
  newArr.count = arr.count - 1;

  newArr.arr = (int *)malloc((arr.count-1)* sizeof(int));

  for (int i=0; i<(arr.count-1); i++){
    newArr.arr[i] = arr.arr[i];
  }
  free(arr.arr);

  return newArr;
}


void output(dynArray_t * arr){
  for (int i = 0; i < (*arr).count; i++){
    printf("%d ", (*arr).arr[i]);
  }
  free((*arr).arr);
}


count_t gameR(int *arrl, int *arrp, int *arrw, int lenl, int lenp, int lenw, int player, count_t count){
  printf("lenp=%d lenl=%d lenw=%d\n", lenp, lenl, lenw);


  if (lenp == 0 && lenl == 1 && lenw == 0) {
    if ('A'+ player == 'A') {
      count.a += arrl[lenl - 1];
      return count;
    }
    else {
      count.b += arrl[lenl - 1];
      return count;
    }
  }
  else if (lenp == 1 && lenl == 0 && lenw == 0){
    if ('A'+ player == 'A') {
      count.a += arrp[lenp - 1];
      return count;
    }
    else {
      count.b += arrp[lenp - 1];
      return count;
    }
  }
  else if (lenp == 0 && lenl == 0 && lenw == 1){
    if ('A'+ player == 'A') {
      count.a += arrw[lenw - 1];
      return count;
    }
    else {
      count.b += arrw[lenw - 1];
      return count;
    }
  }
  else if( lenp > 1 && lenl == 0 && lenw == 0){
    if ('A'+ player == 'A') {
      count.a += arrp[lenp - 1];
      player = !player;
      gameR(arrl, arrp, arrw, lenl, lenp-1, lenw, player, count);
    }
    else{
      count.b += arrp[lenp - 1];
      player = !player;
      gameR(arrl, arrp, arrw, lenl, lenp-1, lenw, player, count);
    }
  }
  else if (lenl > 1 && lenp == 0 && lenw == 0){
    if ('A'+ player == 'A') {
      count.a += arrl[lenl - 1];
      player = !player;
      gameR(arrl, arrp, arrw, lenl-1, lenp, lenw, player, count);
    }
    else{
      count.b += arrl[lenl - 1];
      player = !player;
      gameR(arrl, arrp, arrw, lenl-1, lenp, lenw, player, count);
    }
  }
  else if (lenw > 1 && lenp == 0 && lenl == 0){
    if ('A'+ player == 'A') {
      count.a += arrw[lenw - 1];
      player = !player;
      gameR(arrl, arrp, arrw, lenl, lenp, lenw-1, player, count);
    }
    else{
      count.b += arrw[lenw - 1];
      player = !player;
      gameR(arrl, arrp, arrw, lenl, lenp, lenw-1, player,  count);
    }
  }
  else if (lenw > 0 && lenp > 0 && lenl == 0) {
    count_t res1, res2;
    res1 = gameR(arrl, arrp, arrw, lenl, lenp - 1, lenw, !player, count);
    res2 = gameR(arrl, arrp, arrw, lenl, lenp, lenw - 1, !player, count);

    if ('A' + player == 'A') {
      if (res1.a + arrp[lenp - 1] >= res2.a + arrw[lenw - 1]) {
        res1.a += arrp[lenp - 1];
        return res1;
      }
      else {
        res2.a += arrw[lenw - 1];
        return res2;
      }
    }
    else {
      if (res1.b + arrp[lenp - 1] >= res2.b + arrw[lenw - 1]) {
        res1.b += arrp[lenp - 1];
        return res1;
      }
      else {
        res2.b += arrw[lenw - 1];
        return res2;
      }
    }
  }

  else if (lenw > 0 && lenp == 0 && lenl > 0){
    count_t res1, res2;
    res1 = gameR(arrl, arrp, arrw, lenl - 1, lenp, lenw, !player, count);
    res2 = gameR(arrl, arrp, arrw, lenl, lenp, lenw - 1, !player, count);

    if ('A' + player == 'A') {
      if (res1.a + arrl[lenl - 1] >= res2.a + arrw[lenw - 1]) {
        res1.a += arrl[lenl - 1];
        return res1;
      } else {
        res2.a += arrw[lenw - 1];
        return res2;
      }
    }
    else {
      if (res1.b + arrl[lenl - 1] >= res2.b + arrw[lenw - 1]) {
        res1.b += arrl[lenl - 1];
        return res1;
      } else {
        res2.b += arrw[lenw - 1];
        return res2;
      }
    }
  }
  else if (lenw == 0 && lenp > 0 && lenl > 0){
    count_t res1, res2;
    res1 = gameR(arrl, arrp, arrw, lenl - 1, lenp, lenw, !player, count);
    res2 = gameR(arrl, arrp, arrw, lenl, lenp - 1, lenw, !player, count);

    if ('A' + player == 'A') {
      if (res1.a + arrl[lenl - 1] >= res2.a + arrp[lenp - 1]) {
        res1.a += arrl[lenl - 1];
        return res1;
      } else {
        res2.a += arrp[lenp - 1];
        return res2;
      }
    }
    else {
      if (res1.b + arrl[lenl - 1] >= res2.b + arrp[lenp - 1]) {
        res1.b += arrl[lenl - 1];
        return res1;
      }
      else {
        res2.b += arrp[lenp - 1];
        return res2;
      }
    }
  }
  else{
    count_t res1, res2, res3;
    res1 = gameR(arrl, arrp, arrw, lenl-1, lenp, lenw, !player, count);
    res2 = gameR(arrl, arrp, arrw, lenl, lenp-1, lenw, !player, count);
    res3 = gameR(arrl, arrp, arrw, lenl, lenp, lenw-1, !player, count);

    if ('A'+ player == 'A'){
      if ((res1.a + arrp[lenp-1] >= res2.a + arrl[lenl-1]) && (res1.a + arrp[lenp-1] >= res3.a + arrw[lenw-1])){
        res1.a += arrp[lenp-1];
        return res1;
      }
      else if ((res2.a + arrl[lenl-1] > res1.a + arrp[lenp-1]) && (res2.a + arrl[lenl-1] > res3.a + arrw[lenw-1])){
        res2.a += arrl[lenl-1];
        return res2;
      }
      else if ((res3.a + arrw[lenw-1] >= res1.a + arrp[lenp-1]) && (res3.a + arrw[lenw-1] >= res2.a + arrl[lenl-1])){
        res3.a += arrw[lenw-1];
        return res3;
      }
    }
    else{
      if ((res1.b + arrp[lenp-1] >= res2.b + arrl[lenl-1]) && (res1.b + arrp[lenp-1] >= res3.b+ arrw[lenw-1])){
        res1.b += arrp[lenp-1];
        return res1;
      }
      else if ((res2.b + arrl[lenl-1] > res1.b + arrp[lenp-1]) && (res2.b + arrl[lenl-1] > res3.b + arrw[lenw-1])){
        res2.b += arrl[lenl-1];
        return res2;
      }
      else if ((res3.b + arrw[lenw-1] >= res1.b + arrp[lenp-1]) && (res3.b + arrw[lenw-1] >= res2.b + arrl[lenl-1])){
        res3.b += arrw[lenw-1];
        return res3;
      }
    }
  }
}


int main( void ){
  dynArray_t arrp, arrl, arrw;
  int n, num, player = 0;
  int a;
  count_t count;
  count.a = count.b = 0;

  input(&arrp);
  input(&arrl);
  input(&arrw);

  count = gameR(arrl.arr, arrp.arr, arrw.arr, arrl.count, arrp.count, arrw.count, player, count);
  /*
  printf("Arrl :\n");
  output(&arrp);
  printf("Arrp :\n");
  output(&arrl);
  */
 printf("a=%d b=%d\n", count.a, count.b);

  return 0;

}