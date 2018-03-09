#include<stdio.h>

typedef enum _paddingType { ZERO, HALF, SAME} PaddingType;

/* Kernel array moves on the input array in each iteration and calculates one array element for the output array */
int convolution(double inputArr[], int inputArraySize, double kernelArr[], int
kernelArraySize, double outputArr[], int *outputArraySize, int stride, PaddingType
padding)
{
   
	int i,j,k,temp; 
	int paddingWidth,rightPadding,paddingArraySize;
	double paddingArr[255]; /* Includes the status which is after padding input array */
	double sum = 0;
	
	 if(kernelArraySize < inputArraySize)
	{
		paddingWidth = (kernelArraySize - 1) / 2; /* Calculates the padding width using for adding additional elements to array */
		temp = paddingWidth;
	
	
		for(i = 0 ; i< inputArraySize ; i++) 
		{
			paddingArr[temp] = inputArr[i];		  /* Copies input array to padding array and shifts output array by paddingWidth */
			temp += 1;
		}
	
		paddingArraySize = ( 2 * paddingWidth) + inputArraySize; /* Calculates the size of paddingArr array */
		rightPadding = paddingArraySize - paddingWidth; /* Finds  the place to start adding element for the right side of the array */
		temp = rightPadding;
	
		for(i = 0 ; i < paddingWidth ; i++) 	/* Adds elements to the left and right side according to paddingWith */ 
		{
			switch(padding) 
			{
				/* Adds first and last element of the array to the left and right side respectively */
				case SAME:
					paddingArr[i] = paddingArr[paddingWidth];				/* Adding left side */
					paddingArr[rightPadding] = paddingArr[temp - 1];		/* Adding right side */
					break;
				/*Adds zero to left and right side of array */
				case ZERO:
					paddingArr[i] = 0;										/* Adding left side */
					paddingArr[rightPadding] = 0;							/* Adding right side */
					break;
				/*Adds half of the first and last element of the array to the left and right side respectively */
				case HALF:
					paddingArr[i] = paddingArr[paddingWidth] / 2;			/* Adding left side */
					paddingArr[rightPadding] = paddingArr[temp - 1] / 2;	/* Adding right side */
					break;
				default:
					return (-1);
			}
		
			rightPadding += 1;
		}
		
		/* Takes the paddingArr using for convolution operator */
	
		*outputArraySize = ( (inputArraySize - kernelArraySize + 2 * paddingWidth) / stride ) + 1; /*Calculate the output array size */

		for(j=0;j<*outputArraySize;j++) 
		{	
			k = j * stride; /* Calculates the amount of kernel movement for each iteration */
			
			for(i=0 ; i<kernelArraySize;i++)
			{	
				sum = sum + (kernelArr[i] * paddingArr[k]);
				k += 1;
			}
			outputArr[j] = sum;
			sum = 0;
		}
	
	    return (0);
	}
	else
	{
		return (-1);
	}
}

int main (void)
{
int i;
double inputArr[] = {3, 5, 7, 9, 11, 13, 15};
double kernelArr[] = {-1, 2, 0.5, 4, 1.7};
double outputArr[255];
int outputArrSize = 0;
convolution(inputArr, 7, kernelArr, 5, outputArr, &outputArrSize, 1, SAME);

for(i=0; i< outputArrSize  ; i++)
		printf("%.1f ",outputArr[i]);
	return 0;
}
