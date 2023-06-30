#include <stdio.h>
#include <assert.h>

int isLeap(int year){
	if ((year % 4 == 0 && year % 100 != 0) ||  (year % 400 == 0 && year % 4000 != 0) )
  	return 1;
  else
    return 0;
}

int day(int year, int month, int d1){
	int wday = 0;
  if (month < 3) {
  	--year;
    month += 10;
  } 
  else
  	month -= 2;
  wday = ((d1 + 31 * month / 12 + year + year / 4 - year / 100 + year / 400) % 7);
  if (wday == 0)
  	wday = 7;
  
  return wday;
}

int d1d2(int h1, int i1, int h2, int i2, long long int  *b_1, long long int  *b_2){
        while (h1 < h2){
                for (int i = i1; i <= 60; i++){
                        switch (i){
                                case 0:
                                        *b_1 += 4;
                                        if (h1 % 12 == 0){
                                                *b_2 += 12;
                                        }else {
                                                *b_2 += h1 % 12;
                                        }
                                        break;
                                case 15:
                                        *b_1 += 1;
                                        break;
                                case 30:
                                        *b_1 += 2;
                                        break;
                                case 45:
                                        *b_1 += 3;
                                        break;
                        }
                }
                i1 = 0;
                h1++;
        }
        for (int i = i1; i <= i2; i++){
                        switch (i){
                        case 0:
                                *b_1 += 4;
                                if (h1 % 12 == 0){
                                        *b_2 += 12;
                                }else {
                                        *b_2 += h1 % 12;
                                }
                                break;
                        case 15:
                                *b_1 += 1;
                                break;
                        case 30:
                                *b_1 += 2;
                                break;
                        case 45:
                                *b_1 += 3;
                                break;
                }
        }
        return 1;
}

int d1_pullnoc(int h1, int i1, long long int  *b_1, long long int  *b_2){
        while (h1 < 24){
                for (int i = i1; i < 60; i++){
                        switch (i){
                                case 0:
                                        *b_1 += 4;
                                        if (h1 % 12 == 0){
                                                *b_2 += 12;
                                        }else {
                                                *b_2 += h1 % 12;
                                        }
                                        break;
                                case 15:
                                        *b_1 += 1;
                                        break;
                                case 30:
                                        *b_1 += 2;
                                        break;
                                case 45:
                                        *b_1 += 3;
                                        break;
                        }
                }
                i1 = 0;
                h1++;
        }
        return 1;
}

int pullnoc_d2 (int h2, int i2, long long int  *b_1, long long int  *b_2){
        for (int j = 0; j < h2; j++){
                for (int i = 0; i <= 60; i++){
                        switch (i){
                                case 0:
                                        *b_1 += 4;
                                        if (j % 12 == 0){
                                                *b_2 += 12;
                                        }else {
                                                *b_2 += j % 12;
                                        }
                                        break;
                                case 15:
                                        *b_1 += 1;
                                        break;
                                case 30:
                                        *b_1 += 2;
                                        break;
                                case 45:
                                        *b_1 += 3;
                                        break;
                        }
                }
        }
        for (int i = 0; i <= i2; i++){
                switch (i){
                        case 0:
                                *b_1 += 4;
                                if (h2 % 12 == 0){
                                        *b_2 += 12;
                                }else {
                                        *b_2 += h2 % 12;
                                }
                                break;
                        case 15:
                                *b_1 += 1;
                                break;
                         case 30:
                                *b_1 += 2;
                                break;
                        case 45:
                                *b_1 += 3;
                                break;
                }
        }
        return 1;
}

int count(int year, int month, int day) {
    static int days_before_month[] = {
        0,
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };
    int y = year - 1;
    return day + days_before_month[month] + (isLeap(year) && month > 2) +
          y * 365 + y/4 - y/100 + y/400;
}

/**int day(int y1, int m1, int d1){
	int yearcod, monthcod, step, ccod, res;
	step = 0;
	
	if (y1 > 1699){
		for (int i=1600; i < y1; i += 100)
			step += 1;
	}
	step -= 1;
	if (step > 3)
		step %= 4;
	ccod = 6 - step*2;
	yearcod = (ccod + (y1%100) + (y1%100) / 4) % 7;
	
	switch (m1){
		case 1:
		case 10:
			monthcod = 1;
			break;
		case 5:
			monthcod = 2;
			break;
		case 8:
			monthcod = 3;
			break;
		case 2:
		case 3:
		case 11:
			monthcod = 4;
			break;
		case 6:
			monthcod = 5;
			break;
		case 12:
		case 9:
			monthcod = 6;
			break;
		case 4:
		case 7:
			monthcod = 0;
			break;
	}
	
	res = (d1 + monthcod + yearcod) % 7;
	if (res == 1)
		res = 7;
	else
		res = (res+6) % 7;
	if (isLeap(y1)){
		if (res == 1)
			res = 7;
		else
			res -= 1;
	}
	return res;
}
**/
int bells ( int y1, int m1, int d1, int h1, int i1,
           int y2, int m2, int d2, int h2, int i2,
           long long int * b1, long long int * b2 ){
  int count_days, weekday1, weekday2;
  long long int b11 = 0, b22 = 0;
	
	if (y1 < 1600 || m1 < 1 || m1 > 12 || d1 < 1 || (isLeap(y1) == 0 && m1 == 2 && d1 > 28) || d1 > 31 || h1 < 0 || h1 > 23 || m1 < 0 || m1 > 59)
    return 0;
  if (y2 < 1600 || m2 < 1 || m2 > 12 || d2 < 1 || (isLeap(y2) == 0 && m2 == 2 && d2 > 28) || d2 > 31 || h1 < 0 || h1 > 23 || m1 < 0 || m1 > 59)
    return 0;
	if (y1 > y2)
		return 0;
	else if (y1 == y2 && m1 > m2)
		return 0;
	else if (y1 == y2 && m1 == m2 && d1 > d2)
		return 0;
	else if (y1 == y2 && m1 == m2 && d1 == d2 && h1 > h2)
		return 0;
	else if (y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 > i2)
		return 0;
	
	*b1 = 0;
  *b2 = 0;
	weekday1 = day(y1, m1, d1);
	weekday2 = day(y2, m2, d2);
	
	count_days = count(y2, m2, d2) - count(y1, m1, d1) - 1;
	if (count_days > 0)
		if (count_days > 4){
			if (weekday1 != 7 && weekday2 != 7){
				if (weekday1 > weekday2)
					count_days = (count_days - count_days / 7) - 1;
				else if(weekday1 == weekday2)
					count_days = count_days - (count_days+1) / 7;
				else
					count_days = count_days - count_days / 7;	
				
				*b1 = count_days * 240;
				*b2 = count_days * 156;
				d1_pullnoc(h1, i1, &b11, &b22);
				pullnoc_d2(h2, i2, &b11, &b22);
				*b1 += b11;
				*b2 += b22;
			}
			else if (weekday1 == 7 && weekday2 == 7){
				*b1 = count_days * 240;
				*b2 = count_days * 156;
			}
			else if (weekday1 == 7){
				count_days = count_days - count_days / 7;
				*b1 = count_days * 240;
				*b2 = count_days * 156;
				pullnoc_d2(h2, i2, &b11, &b22);
				*b1 += b11;
				*b2 += b22;
			}
			else if (weekday2 == 7){
				count_days = count_days - count_days / 7;
				*b1 = count_days * 240;
				*b2 = count_days * 156;
				d1_pullnoc(h1, i1, &b11, &b22);
				*b1 += b11;
				*b2 += b22;
			}
		}	
		else if (weekday1 > 2 && (weekday1 + count_days) > 6){
			if (weekday1 != 7 && weekday2 != 7){
				*b1 = (count_days-1) * 240;
				*b2 = (count_days-1) * 156;
				d1_pullnoc(h1, i1, &b11, &b22);
				pullnoc_d2(h2, i2, &b11, &b22);
				*b1 += b11;
				*b2 += b22;
			}
			else if (weekday1 == 7){
				*b1 = (count_days) * 240;
				*b2 = (count_days) * 156;
				pullnoc_d2(h2, i2, &b11, &b22);
				*b2 += b22;
				*b1 += b11;
			}
			else if (weekday2 == 7){
				*b1 = (count_days) * 240;
				*b2 = (count_days) * 156;
				d1_pullnoc(h1, i1, &b11, &b22);
				*b1 += b11;
				*b2 += b22;
			}
		}
		else{
			*b1 = count_days * 240;
			*b2 = count_days * 156;
			d1_pullnoc(h1, i1, &b11, &b22);
			pullnoc_d2(h2, i2, &b11, &b22);
			*b1 += b11;
			*b2 += b22;
		}
	else if (count_days == 0){
		if (weekday1 == 7){
			pullnoc_d2(h2, i2, &b11, &b22);
			*b1 += b11;
			*b2 += b22;
		}
		else if (weekday2 == 7){
			d1_pullnoc(h1, i1, &b11, &b22);
			*b1 += b11;
			*b2 += b22;
		}
		else{
			d1_pullnoc(h1, i1, &b11, &b22);
			pullnoc_d2(h2, i2, &b11, &b22);	
			*b1 += b11;
			*b2 += b22;
		}
	}
	else{
		if (weekday1 != 7){
			d1d2 (h1, i1, h2, i2, &b11, &b22);
			*b1 += b11;
			*b2 += b22;
		}
	}

	return 1;
}


int main ( int argc, char * argv [] )
{
  long long int b1=0, b2=0;
	
	assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  1, 18, 45, &b1, &b2 ) == 1
           && b1 == 56
           && b2 == 20 );
  assert ( bells ( 2022, 10,  3, 13, 15,
                   2022, 10,  4, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  2, 11, 20, &b1, &b2 ) == 1
           && b1 == 106
           && b2 == 65 );
  assert ( bells ( 2022, 10,  2, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 115
           && b2 == 78 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  
  assert ( bells ( 2022,  1,  1, 13, 15,
                   2022, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 56861
           && b2 == 36959 );
  assert ( bells ( 2019,  1,  1, 13, 15,
                   2019, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
  assert ( bells ( 2024,  1,  1, 13, 15,
                   2024, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57341
           && b2 == 37271 );
  assert ( bells ( 1900,  1,  1, 13, 15,
                   1900, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 ); 
  assert ( bells ( 2022, 10,  1,  0,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 124
           && b2 == 90 );
  assert ( bells ( 2022, 10,  1,  0, 15,
                   2022, 10,  1,  0, 25, &b1, &b2 ) == 1
           && b1 == 1
           && b2 == 0 );
  assert ( bells ( 2022, 10,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 11,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 10, 32, 12,  0,
                   2022, 11, 10, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2100,  2, 29, 12,  0,
                   2100,  2, 29, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2000,  2, 29, 12,  0,
                   2000,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2004,  2, 29, 12,  0,
                   2004,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 0
           && b2 == 0 );
  bells ( 2053,  8, 9, 0,  0, 2053,  8, 9, 0, 15, &b1, &b2); 
	printf("%lld %lld\n", b1, b2);
  return 0;
}
