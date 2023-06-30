#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>


void alloc_free(char **names, int count, double*xs, double *ys, int flag){
	if (flag){
		for (int i=0; i < count; i++)
			free(names[i]);
		free(names);
		free(xs);
		free(ys);
	}
	else{
		free(names);
		free(xs);
		free(ys);
	}
} 

double f_dist(double x, double y){
	return sqrt(x*x+y*y);
}

int equality(double x, double y) {
	double diff = fabs(x - y);
	x = fabs(x);
	y = fabs(y);
	const double sE = DBL_EPSILON * fmax(x, y);
  return diff <= sE;
}

int main( void ){
	double *xs=NULL, *ys=NULL;
	int length, count, res, pairs, len1, len2, len_m=3;
	double x, y, min, dist; 
	char name[200];
	char mask[4]=" - "; 
	char ** names;
	char ** results;
	length = 2;
	count = 0;
	min = 1.79769e+308;
	pairs = 0;
	/*
	xs = (double*)malloc(length * sizeof(double));
	ys = (double*)malloc(length * sizeof(double));
	names = (char**)malloc(length*sizeof(char*));
	results = (char**)malloc(1*sizeof(char*));
	
	printf("Pozice letadel:\n");
	
	res = scanf(" %lf, %lf: %s", &x, &y, name);
	if (res != 3){
    printf("Nespravny vstup.\n");
    alloc_free(names, 1, xs, ys, 0);
    return 1;
  }
  
	while( res != EOF){
		if (res != 3){
      printf("Nespravny vstup.\n");
      alloc_free(names, count, xs, ys, 1);
      return 1;
    }
    
		if (count == length){
      length *= 2;
      xs = (double*)realloc(xs,length * sizeof(double));
			ys = (double*)realloc(ys,length * sizeof(double));
			names = (char**)realloc(names,length*sizeof(char*));
    }
    
    xs[count] = x;
    ys[count] = y;
    names[count] = (char*)malloc(200*sizeof(char));
    strcpy(names[count], name);
    count++;
    res = scanf(" %lf, %lf: %s", &x, &y, name);
	}
	
	if (count < 2){
		printf("Nespravny vstup.\n");
		alloc_free(names, count, xs, ys, 1);
    return 1;
	}
	
	
	for (int i=0; i < (count - 1); i++){
    for (int j=i+1; j < count; j++){
    	dist = f_dist(xs[j]-xs[i], ys[j]-ys[i]);
				printf("d=%.20lf\n", dist);
    	if(equality(dist, min)){
    		len1 = strlen(names[i]);
    		len2= strlen(names[j]);
    		pairs += 1;
    		
    		results = (char**)realloc(results, pairs*sizeof(char*));
    		results[pairs-1] = (char*)malloc((len1 + len2 + 4)*sizeof(char));
    		
    		memcpy(results[pairs-1], names[i], len1);
    		memcpy(results[pairs-1] + len1, mask, len_m);
        memcpy(results[pairs-1] + len1 + len_m, names[j], len2 + 1);
    	}
    	if (dist < min){
    		pairs = 0;
    		min = dist;
    		len1 = strlen(names[i]);
    		len2= strlen(names[j]);
    		
    		results = (char**)malloc(1*sizeof(char*));
    		results[pairs] = (char*)malloc((len1 + len2 + 4)*sizeof(char));
    		
    		memcpy(results[pairs], names[i], len1);
    		memcpy(results[pairs] + len1, mask, len_m);
        memcpy(results[pairs] + len1 + len_m, names[j], len2 + 1); 
        
        pairs++;
    	}
    }	
	}	

	printf("Vzdalenost nejblizsich letadel: %f\n", min);
	printf("Nalezenych dvojic: %d\n", pairs);	
	
	for (int i=0; i<pairs; i++)
		printf("%s\n", results[i]);
	
	
	for (int i=0; i < pairs; i++)
			free(results[i]);
	free(results);
	alloc_free(names, count, xs, ys, 1);
	*/
	
	double resul = 6.09999999999998365752;
	double answ = 6.09999999999990905053;
	double diff = fabs(resul - answ);
	resul = fabs(resul);
	answ = fabs(answ);
	/*for (double i=1; i>1e-50; i /= 10){
		const double sE = i * fmax(resul, answ);
  	if(diff <= sE)
			printf("%.20lf\n", i);	
  }
	*/

	//double diff = fabs(resul - answ);
	//resul = fabs(resul);
	//answ = fabs(answ);
	const double sE = 1e-13 * fmax(resul, answ);
  if(diff <= sE)
		printf("%.20lf\n", 2.0);
	printf("%d \n", equality(resul, answ));


  return 0;
}	
