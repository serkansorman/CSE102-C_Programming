#include<stdio.h>


int isPrime(int num);	/* Checks whether given	integer	is	a prime	number or not */

int goldbach(int num, int *p1, int *p2); /* Displays the given even number as the sum of two prime numbers */



/* Checks whether given	integer	is	a prime	number or not.Return 1 if num is prime, 0 otherwise.*/
int isPrime(int num)	
{
	int counter = 1 ;
	int flag = 1 ; /* Used to finish the loop */
	int remainder ;
	int status;
	
	if(num > 1)										
	{
		while(counter < num && flag == 1)  /* The numbers up to the given number are found */
		{	
			remainder = num % counter;		/* Calculates the remainder obtained from division */
		
			if(remainder == 0 && counter != 1 )	 /* if remainder is equal to 0 except the division by 1,the number is not prime */
			{	
				status =  0;			/* Makes the status 0 and finishes the loop by flag */
				flag = 0;			
			}
			
			else					/*In other cases the number is prime number.Makes the status 1 */
			{
				status = 1; 
			}
			
			counter ++;				
		}
		
		return status;					/* Return 1 if num is prime, 0 otherwise. */
	}
	else
		return 0;						
}

/* Takes an	integer	and	returns	two	prime numbers whose	sum	is	equal to given	integer. */	
int goldbach(int num,int *p1, int *p2)
{

	int i,j,sum;
	
	if(num > 2 && num % 2 == 0)              /* Checks whether the number is even or not and more than two */
	{
		for(i = 2; i < num ; i++)			
		{	
			if(isPrime(i)  && isPrime(num - i)){/*Checks sum of two prime number is target number */
				*p1 = i;
				*p2 = num - i;
				return 1;		/* return 1 if num is even and two prime numbers found */
			}			
		}
	}
	else	
		return 0;	/* return 0 otherwise */	
		
}
				
int main(void)
{
	int num = 488,p1, p2;
	if(goldbach(num,&p1,&p2))
		printf("%d = %d + %d",num,p1,p2);

	else
		printf("You should provide even number.");



	return 0;
}
