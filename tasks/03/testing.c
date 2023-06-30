#include <stdio.h>

int isLeap(int year){
	if ((year % 4 == 0 && year % 100 != 0) ||  (year % 400 == 0 && year % 4000 != 0) )
  	return 1;
  else
    return 0;
}

int ymd_to_ord(int year, int month, int day) {
    static int days_before_month[] = {
        0,
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };
    int y = year - 1;
    return day + days_before_month[month] + (isLeap(year) && month > 2) +
          y * 365 + y/4 - y/100 + y/400;
}
/**
int day(int y1, int m1, int d1){
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
	printf
	
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
int weekday(int year, int month, int day){
	int wday = 0;
  if (month < 3) {
  	--year;
    month += 10;
  } 
  else
  	month -= 2;
  wday = ((day + 31 * month / 12 + year + year / 4 - year / 100 + year / 400) % 7);
  if (wday == 0)
  	wday = 7;
  
  return wday;
}
int main(){
	int r, r2;
	r = weekday(1900, 10, 5);
	printf("%d\n", r);
	
	return 0;
}		

