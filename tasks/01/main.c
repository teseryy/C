#include <stdio.h>
#include <math.h>

int main(){
  double credit_p=0.0, debit_p=0.0, ac=0.0, tmp=0.0; 
  int op_day=0, current_day=0, payment=0, i;

  printf("Zadejte kreditni urok [%%]:\n");
  if (scanf("%lf", &credit_p) != 1){
    printf("Nespravny vstup.\n");
    return 1;
  }
  credit_p = (credit_p*100)/100;

  printf("Zadejte debetni urok [%%]:\n");
  if (scanf("%lf", &debit_p) != 1){
    printf("Nespravny vstup.\n");
    return 1;
  }
  debit_p = (debit_p*100)/100;
  
  printf("Zadejte transakce:\n");
  if (scanf("%d, %d", &current_day, &payment) != 2){
    printf("Nespravny vstup.\n");
    return 1;
  }
  ac = 1.0*payment;

  while (payment != 0){
    if (scanf("%d, %d", &op_day, &payment) != 2 || op_day <= current_day){
      printf("Nespravny vstup.\n");
      return 1; 
    }  
    
    if (ac >= 0){
      for (i = current_day; i < op_day; i++){
        tmp = ac*credit_p/100;
        ac += tmp;
        ac = floor(ac*100)/100;
      }
    }
    else{
      for (i = current_day; i < op_day; i++){
        tmp = ac*debit_p/100;
        ac += tmp;
        ac = ceil(ac*100)/100;
      }
    }
    
    ac += payment;
    current_day = op_day;
  }
  
  printf("Zustatek: %.2f\n", ac);

  return 0;
}
