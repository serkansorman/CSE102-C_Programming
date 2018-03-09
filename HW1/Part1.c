#include<stdio.h>
#define day_in_year 365
#define day_in_month 30

int theAge(int day,int month, int year, int today,int this_month, int this_year ); 	/* Calculete the age of user */

int daysLeft(int day,int month, int today,int this_month); 		/* Calculete the number of days to the birthday */


int main(void)
{
daysLeft(28,6,25,2);
theAge(28,6,1996,25,2,2017);
	
	return (0);
}


int daysLeft(int day,int month, int today,int this_month)
{
	int sum_birth_date , sum_today , days_left;

	/* Months in dates are converted to day */
	sum_birth_date = day + (month * day_in_month);				
	sum_today = today + (this_month * day_in_month);			
	days_left = (sum_birth_date - sum_today + day_in_year) % day_in_year; 

	printf("%d  ",days_left);

	return (days_left);
}



int theAge(int day,int month, int year, int today,int this_month, int this_year )
{
	int total_user_days , total_current_days , Age ;

	/* Months and years in dates are converted to day */
	total_user_days = day + (month * day_in_month) + (year * day_in_year);		
	total_current_days = today + (this_month * day_in_month) + (this_year * day_in_year);
	Age = (total_current_days - total_user_days) / day_in_year;

	printf("%d",Age);

	return (Age);
}


