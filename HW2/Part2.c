#include<stdio.h>

double root(double number); /* Calculate square root of given number */

void drawRectangle(int width,int height, int startingPoint, int printLastLine); /* Draw  hollow rectangle */

void drawDoubleCircle(int radius, int startingPoint , int whellDistance); /* Draws two equal circles Which have space between them */

void drawCar(); /* Use rectangle and circle functions and draw car */



double root(double number) /* Calculate square root of given number */
{
	double i, temp;
	temp = number;
	for (i = 0; i <= number/2; i++)
		temp = ((temp + (number / temp)) / 2);
	return temp;
}

void drawRectangle(int width,int height, int startingPoint, int printLastLine)
{

	int i,j;
	int start_space; /* Counter for startingPoint */
	
	for(i=1;i<=height;i++)   /* Draw height of rectangle until i equal to parameter height */
	{
		for(j=1;j<=width;j++) /* Draw width of rectangle until j equal to parameter width */
		{
			if(i == 1 || j == 1 || j == width || i == height * printLastLine) /* Print last line of rectangle according to whether the 	parameter is 1 or 0 */
			{	
				if(j==1)	/* Before the draw rectangle,space out according to the desired starting point */
				{
					for(start_space = 1 ; start_space < startingPoint ; start_space++)
						printf(" "); 
				}
				printf("*"); /* Print first and last lines of rectangle */
				
			}
			else
				printf(" "); /* Space out except the first and last lines */
		}
		printf("\n");
	}
}


void drawDoubleCircle(int radius, int startingPoint , int whellDistance) /* Draws two equal circles Which have space between them */
{
	int x , y, i;
	int start_space; /* Counter of starting point for circle */
	int wheel_space; /* Counter of distance between circles */
    double dist1,dist2; /* Distances from the center of the circles */
	
    
    for (x = 0;  x < radius * radius ; x++)
    {	
        for(start_space = 1 ; start_space < startingPoint ; start_space++) /* Space for starting point of circle */
		    printf(" ");
        for (y = 0; y <= radius * radius; y++) /* Using the circle equation, the distances from the center are calculated */
        {
            dist1 = root( (x - radius) * (x - radius) + (y - radius) * (y - radius) );			/*Distance for the first circle*/
            dist2 = root( (x - radius) * (x - radius) + (y - radius * 3) * (y - radius * 3) );	/*Distance for the second circle */
            
           	if( x == radius && y == radius * 2) /* Put star to the empty coordinate in circle */
           		printf("*");
          	
			for(i = 0 ; i <= 2 * radius ; i++) /*In this part, set distance between circles*/
			{
            	if(x == i && y == 2 * radius)	/* Set distance for between the horizontal center lines of circles */
            	{	
            	    if(x == radius && y == radius * 2)
            		{
		    			for(wheel_space = 0 ; wheel_space < whellDistance ; wheel_space ++)
		    				printf(" ");
		    				
		    			if(wheel_space == whellDistance - 1)
		    				printf(" ");
            		}
            		
            		else /* Set the distance between circles for other horizontal lines */
            		{	
            			for(wheel_space = 0 ; wheel_space <= whellDistance ; wheel_space ++)
            				printf(" ");
            		}
        		}	
        	}
            if (dist1 <= radius  || dist2 <= radius || (x == radius && y == radius) || (x == radius && y == radius * 3))
            	printf("* ");  /* If the distance from center of circle less than radius, prints star */
            			   		/* and prints star on centers of circles */
			else
        	    printf("  ");	/* Space out for remaining fields */
        }
        printf("\n");			/* New line for  continue drawing circle */
    }
}

void drawCar() /* Use rectangle,circle functions and draw car */
{
drawRectangle(40,10,11,0);
drawRectangle(60,10,0,1);
drawDoubleCircle(4,7,12);
}
int main(void){
drawCar();




	return (0);
}
