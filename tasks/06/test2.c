#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

typedef struct{
  char ** arr;
  int length;
  int cur_l;
} dynArr_t;

typedef struct{
  char num;
  dynArr_t products;
} rack_t;

typedef struct{
  int num;
  char * str;
} counted_t;

void removeNL( char str[]){
	size_t len = strlen(str);
	if (len > 1 && str[len-1] == '\n')
		str[len-1] = '\0';
}

int readR( rack_t ** racks){
  size_t len=0;
	char * prod=NULL;
	int count_r=-1;
	int length = 1, res;

  *racks = (rack_t*)malloc(length*sizeof(rack_t));
  (*racks)[0].products.length = 1;
  (*racks)[0].products.cur_l = 0;
  getline(&prod, &len, stdin);
  
  
  if( (prod[0] == '#' && strlen(prod)<2) || (prod[0] == '#'&& (int)prod[1] != 48 ) || prod[0] != '#'){
  	free((*racks));
  	free(prod);
  	return -1;
  }
	
  while( prod[0] != '\n'){
  	
  	if( (prod[0] == '#' && strlen(prod)<2) || (prod[0] == '#'&& ((int)prod[1] < 48 || (int)prod[1] > 57))){
  		for (int i=0; i <= count_r; i++){
  			if ((*racks)[i].products.cur_l > 0)
  				for (int j=0; j < (*racks)[i].products.cur_l; j++)
  					free((*racks)[i].products.arr[j]);
  			free((*racks)[i].products.arr);
  		}
  		free((*racks));
  		free(prod);
  		return -1;
  	}
  
    
    if (prod[0] == '#'){
      count_r++;
      if (count_r == length){
      	length *= 2;
      	*racks = (rack_t*)realloc(*racks, length*sizeof(**racks));
      }
      (*racks)[count_r].products.length = 1;
  		(*racks)[count_r].products.cur_l = 0;
  		(*racks)[count_r].products.arr = (char**)malloc((*racks)[count_r].products.length*sizeof(char*));
	
      (*racks)[count_r].num = (int)prod[1] - 48;
     
      if ( count_r > 0 && (*racks)[count_r].num - (*racks)[count_r-1].num != 1){
  			for (int i=0; i <= count_r; i++){
  				if ((*racks)[i].products.cur_l > 0)
  					for (int j=0; j < (*racks)[i].products.cur_l; j++)
  						free((*racks)[i].products.arr[j]);
  				free((*racks)[i].products.arr);
  			}
  			free((*racks));
  			free(prod);
  			return -1;
      }
    }
    else{
    	if ((*racks)[count_r].products.cur_l == (*racks)[count_r].products.length){
				(*racks)[count_r].products.length *= 2;
				(*racks)[count_r].products.arr = (char **)realloc((*racks)[count_r].products.arr, (*racks)[count_r].products.length*sizeof(char *));
			}
      (*racks)[count_r].products.arr[(*racks)[count_r].products.cur_l] = (char *)malloc((strlen(prod)+1)*sizeof(char));
      strcpy((*racks)[count_r].products.arr[(*racks)[count_r].products.cur_l], prod);
		  (*racks)[count_r].products.cur_l++;
    }
    
		free(prod);
		len = 0;
		res = getline(&prod, &len, stdin);

		if (res < 0){
			for (int i=0; i <= count_r; i++){
  			if ((*racks)[i].products.cur_l > 0)
  				for (int j=0; j < (*racks)[i].products.cur_l; j++)
  					free((*racks)[i].products.arr[j]);
  			free((*racks)[i].products.arr);
  		}
  		free((*racks));
  		free(prod);
  		return -1;
  	}
		
		
		removeNL(prod);
  }
  
  
  free(prod);
  return count_r;
}

int readS( dynArr_t * sez){
	size_t len=0;
	char * prod=NULL;
	(*sez).length = 1;
	(*sez).cur_l = 0;
	
	(*sez).arr = (char **)malloc((*sez).length * sizeof(char*));
	
	while (getline(&prod, &len, stdin) >= 0){
		removeNL(prod);
		if ((*sez).length == (*sez).cur_l){
			(*sez).length *= 2;
			(*sez).arr = (char **)realloc((*sez).arr, (*sez).length * sizeof(char*));
		}
		
		(*sez).arr[(*sez).cur_l] = (char *)malloc((strlen(prod)+1)*sizeof(char));
		strcpy((*sez).arr[(*sez).cur_l], prod);
		(*sez).cur_l++;
		
		free(prod);
		len = 0;
	}
	if ((*sez).cur_l == 0){
		free((*sez).arr);
		return -1;
	}
	else
		free(prod);
	return 0;
}

void search( dynArr_t * sez, rack_t ** racks, int count_r, counted_t ** opt_sez ){
	char * isSubstr, *tmp=NULL;
	int flag = -1, finded = 0;
	int isSamestr = -1;
	int nums_bytes, cur_rack=0; 
	char mask[6] = " -> #", nFmask[8] = " -> N/A";
	*opt_sez = (counted_t *)malloc((*sez).cur_l * sizeof(counted_t));

	for (int i=0; i < (*sez).cur_l; i++){
		for (int q=0; q < count_r; q++){
			for (int j=0; j < (*racks)[q].products.cur_l; j++){
				isSubstr = strcasestr((*racks)[q].products.arr[j], (*sez).arr[i]);
				if (isSubstr != NULL){
					finded = 1;
					isSamestr = strcasecmp((*racks)[q].products.arr[j], (*sez).arr[i]);
					if (isSamestr == 0){
						if (q == 0)
							nums_bytes = 1;
						else
							nums_bytes = (int)log10(q)+1;
						(*opt_sez)[i].str = (char *)malloc((strlen((*sez).arr[i])+strlen((*racks)[q].products.arr[j])+nums_bytes+8)*sizeof(char));
						sprintf((*opt_sez)[i].str, "%s%s%d %s", (*sez).arr[i], mask, q, (*racks)[q].products.arr[j]);
						(*opt_sez)[i].num = q;
						break;
						}
					else if (flag == -1){
						tmp = (char *)malloc((strlen((*racks)[q].products.arr[j])+1) * sizeof(char));
						strcpy(tmp, (*racks)[q].products.arr[j]);
						cur_rack = q;
						flag = 0;
					}
				}
			}
			if (finded){
				if (isSamestr == 0){
					if (flag == 0){
						flag = -1;
						free(tmp);
					}
					break;
				}
			}
		}
		if (finded){
			finded = 0;
			if (isSamestr != 0){
				if (cur_rack == 0)
						nums_bytes = 1;
				else
					nums_bytes = (int)log10(cur_rack)+1;
				(*opt_sez)[i].str = (char *)malloc((strlen((*sez).arr[i])+strlen(tmp)+nums_bytes+8)*sizeof(char));
				sprintf((*opt_sez)[i].str, "%s%s%d %s", (*sez).arr[i], mask, cur_rack, tmp);
				(*opt_sez)[i].num = cur_rack;
				flag = -1;
				free(tmp);
			}
		}
		else{
			(*opt_sez)[i].str = (char *)malloc((strlen((*sez).arr[i])+8)*sizeof(char));
			sprintf((*opt_sez)[i].str, "%s%s", (*sez).arr[i], nFmask);
			(*opt_sez)[i].num = INT_MAX;
		}
	}

}


void sortS( dynArr_t * sez, counted_t ** opt_sez){
	counted_t tmp;
	char * str=NULL;
	int counter = 0, move = 3, nums_bytes;
	
	for (int i=(*sez).cur_l-1; i>=0; i--){
		for (int j=0; j < i; j++){
			if ((*opt_sez)[j].str[0] != '\n'){
				if( (*opt_sez)[j].num > (*opt_sez)[j + 1].num){
					tmp = (*opt_sez)[j];
					(*opt_sez)[j] = (*opt_sez)[j + 1];
					(*opt_sez)[j + 1] = tmp;
				}
			} 
		}
	}
	
	for (int i=0; i < (*sez).cur_l; i++){
	
		if ((*opt_sez)[i].str[0] != '\n'){
			if (i == 0)
				nums_bytes = 1;
			else
				nums_bytes = (int)log10(i)+1;
			move += nums_bytes;
			
			str = (char *)malloc((strlen((*opt_sez)[i].str)+move+1)*sizeof(char));
			sprintf(str, " %d. %s", counter, (*opt_sez)[i].str);
			(*opt_sez)[i].str = (char *)realloc((*opt_sez)[i].str, (strlen((*opt_sez)[i].str)+move+1)*sizeof(char));
			strcpy((*opt_sez)[i].str, str);
			free(str);
			
			counter++;
		}
		else
			counter = 0;	
	}
}


int main( void ){
  rack_t * racks;
  dynArr_t seznam;
  counted_t * opt_seznam;
  int count_r=0, err_check;
 	

  if ((count_r = readR(&racks) + 1) == 0){
  	printf("Nespravny vstup.\n");
  	return 1;
  }
	

	if((err_check = readS(&seznam)) != 0){
		printf("Nespravny vstup.\n");
		for (int i=0; i<count_r; i++){
    	for (int j=0; j<racks[i].products.cur_l; j++){
      	free(racks[i].products.arr[j]); 
    	}
    	free(racks[i].products.arr);
  	}
  	return 1;
	}
	
  search(&seznam, &racks, count_r, &opt_seznam);
  
	sortS(&seznam, &opt_seznam);
	
  for (int i=0; i<count_r; i++){
    for (int j=0; j<racks[i].products.cur_l; j++){
      free(racks[i].products.arr[j]); 
    }
    free(racks[i].products.arr);
  }
  
  printf("Optimalizovany seznam:\n");
  for (int i=0; i<seznam.cur_l; i++){
  	if (opt_seznam[i].str[0] != '\n')
  		printf("%s\n", opt_seznam[i].str);
  	else
  		printf("Optimalizovany seznam:\n");
  	free(seznam.arr[i]);
  	free(opt_seznam[i].str);
  } 
  free(seznam.arr);
  free(opt_seznam);
  
  free(racks);
  return 0;
}
