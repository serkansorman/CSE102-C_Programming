#include<stdio.h>
/*Function prototypes */

/*Takes an array and adds padding (additional array elements) to left and right side of this array.*/
void addPadding(double inputArr[], int inputArraySize, double outputArr[], int
*outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));

/*Adds zero to left and right side of input array */
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);

/*Adds first and last element of the array to the left and right side respectively*/
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);

/*Adds half of the first and last element of the array to the left and right side respectively*/
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);




/*Takes an array and adds padding (additional array elements) to left and right side of this array.*/
void addPadding(double inputArr[], int inputArraySize, double outputArr[], int
*outputArraySize, int paddingWidth, void paddingMethod(double[], int, int))
{
	int i,temp;
	
	temp=paddingWidth;
	
	for(i = 0 ; i< inputArraySize ; i++)
	{
		outputArr[temp] = inputArr[i];		/*Copies input array to output array and shifts output array by paddingWidth*/
		temp += 1;
	}
	*outputArraySize = ( 2 * paddingWidth) + inputArraySize;	/* Calculate the output array size */
	paddingMethod(outputArr, *outputArraySize, paddingWidth);	/*Padding values are assigned by calling the addPadding function in 																  paddingMethod parameter.*/

}


/*Adds first and last element of the array to the left and right side respectively*/
void samePadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i,rightPadding,temp;
	
	rightPadding = outputArraySize - paddingWidth; /*Finds  the place to start adding element for the right side of the array */
	temp = rightPadding;
	
	for(i = 0 ; i < paddingWidth ; i++) 				/* Adds elements to the left and right side according to paddingWith */
	{
		outputArr[i] = outputArr[paddingWidth]; 		/* Adds elements to the left side of array */
		outputArr[rightPadding] = outputArr[temp - 1]; 	/* Adds elements to the right side of array */
		rightPadding += 1;
	}
}


/*Adds zero to left and right side of input array */
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i,rightPadding;
	
	rightPadding = outputArraySize - paddingWidth; /*Finds  the place to start adding zero for the right side of the array */

	for(i = 0 ; i < paddingWidth ; i++)			/* Adds zero to the left and right side according to paddingWith */
	{
		outputArr[i] = 0;						/* Adds zero the left side of array */ 	
		outputArr[rightPadding] = 0;			/* Adds zero to the right side of array */
		rightPadding += 1;
	}
}



/*Adds half of the first and last element of the array to the left and right side respectively */
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth)
{
	int i,rightPadding,temp;
	
	rightPadding = outputArraySize - paddingWidth; /*Finds  the place to start adding element for the right side of the array */
	temp = rightPadding;
	
	for(i = 0 ; i < paddingWidth ; i++)						/* Adds elements to the left and right side according to paddingWith */
	{
		outputArr[i] = outputArr[paddingWidth] / 2;			/* Adds elements to the left side of array */	
		outputArr[rightPadding] = outputArr[temp - 1] / 2;	/* Adds elements to the right side of array */
		rightPadding += 1;
	}
}


int main(void)
{
int i;

double inputArr[] = {5,6,7,8,9};
double outputArr[255];
int outputArrSize = 0;
addPadding(inputArr, 5 , outputArr, &outputArrSize, 4, halfPadding);

for(i=0; i< outputArrSize ; i++)
	printf("%.1f ",outputArr[i]);

}
