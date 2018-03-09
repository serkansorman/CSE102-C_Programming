#include<stdio.h>

int dispenseChange(double paid, double due, int *tl1, int *krs50, int *krs25,int *krs10, int *krs5 ,int *krs1)
{
	double change;
	*tl1 = 0, *krs50 = 0, *krs25 = 0,*krs10 = 0,*krs5 = 0, *krs1 = 0;
	
	change = paid - due;
	
	
	if (change >= 0)
	{
		*tl1 = change / 1;
		change -=  *tl1 ;	 
		
		*krs50 = change / 0.5;
		 change -= *krs50 * 0.5 ; 
		 
		*krs25 = change / 0.25;
		change -= *krs25 * 0.25 ;
		
		*krs10 = change / 0.1;
		change -= *krs10 * 0.1 ;
			
		*krs5 = change / 0.05;
		change -= *krs5 * 0.05 ;
			
		*krs1 = change / 0.01 ;
			
	
		return 1;
	}
	
	else
		return 0;
	
}		


int main(void)
{
double paid = 1, due = 0.73;
int tl1,krs50,krs25,krs10,krs5,krs1;
if(dispenseChange(paid,due,&tl1,&krs50, &krs25, &krs10, &krs5, &krs1)) /* returns 1 */
printf("Change: 1TL:%d, Kurus- 50:%d  25:%d  10:%d  5:%d  1:%d\n",tl1,krs50,krs25,krs10,krs5,krs1);
else
printf("Unable to dispense change.");



	return 0;
}
