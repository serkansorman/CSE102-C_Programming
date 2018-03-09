#include<stdio.h>

int fTheFunction(int x, int functionNumber){
	
	int i;
	if (functionNumber == 1)
		return 2 * x;

	for(i=2; i<6; ++i)
		if(functionNumber == i)
			return (i+1) * x;
}


void drawFunction(int xAxis,int yAxis,int functionNumber); 


/* Draws the x and y axes according to the given parameters and plots the graph of a given function  */
void drawFunction(int xAxis,int yAxis,int functionNumber){
	
	int i,j,temp;
	int space;		 /* Spaces for drawing function graph */
	int coefficient; /* Coefficient of  given function */
	int result; 	 /* Result calculated by fTheFunction */

	result = fTheFunction(xAxis,functionNumber); /* Received parameters are sent to the function */
	coefficient = result / xAxis;	/* The function coefficient is obtained by using the calculated result */
	space = yAxis / coefficient ; 	
	
	if(coefficient == 1)		/* If the function coefficient is 1, the counter "i" starts from 0 . In all other cases it starts from 1 */
		temp = 0;
	else
		temp = 1;
	
	for(i=temp; i<=yAxis; i++){	/* Draws y-axis of the function graph */
			
		printf("|");	
		for(j=1; j<= xAxis;j++)	 /* Draws the x-axis at the bottom of the function graph */
			if(i==yAxis)	
				printf("-");
				
		for(j=1; j<=space ; j++){ /* Reduces the number of spaces on each line by one and draws the function graph */	
			if(j != space)
				printf(" ");
			else if( ( j == space  && coefficient == 1) || (j == space && i % coefficient == 1) ){
				printf("*");
				space -= 1; 
		 	}
		}
	   	printf("\n");     /* New line for  continue drawing function graph */
	}
}

int main(void){
drawFunction(40,40,1);


	return (0);
}
