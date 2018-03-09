#include<stdio.h>

int charge(int cardType, int* monthlyUse, double* balance)
{
 switch(cardType)
 {
 	case 1:
 	if(*monthlyUse >= 1  )
	 	*monthlyUse -= 1;
 	else if(*monthlyUse < 1 && *balance > 2.30)
	 	*balance -= 2.30;
	else
		return -1;
 	break;
 	
 	
 	case 2:
 	if( *monthlyUse >= 1)
	 	*monthlyUse -= 1;
	else if(*monthlyUse < 1 && *balance > 1.15)
	 	*balance -= 1.15;
	else
 		return -1;
 	break;
 	
 	
 	case 3:
 	if(*monthlyUse >= 1)
		*monthlyUse -= 1;
	else if(*monthlyUse < 1 && *balance > 1.65)
	 	*balance -= 1.65;
	else 
		return -1;
 	break;
 	
 	default:
 		return -2;
 }
 
 	return 0;
}


int main(void)
{
int monthlyUse = 2;
double balance = 2.75;
if(charge(1,&monthlyUse, &balance) == 0)
printf("Remaining monthly use:%d  Remaining Balance: %.2f\n",monthlyUse,balance);
else
printf("Insufficient balance.");
	



	return 0;
}
