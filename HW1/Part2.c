#include<stdio.h>
#define PI 3.14

float diameter(float circumference)
{
	float diameter_tree,growth_factor;
	
	printf("Enter value of circumference: ");
	scanf("%f",&circumference);

	diameter_tree = circumference / PI;


	return (diameter_tree);
}


float ageOfTree(float diameter , float growth_factor)
{
	float age_tree;
	
	printf("Enter value of growth factor: ");
	scanf("%f",&growth_factor);

	age_tree = diameter * growth_factor;
	return (age_tree);
}


int main(void)
{
float growth_factor,circumference;
float dia = diameter(circumference);
float age = ageOfTree(dia, growth_factor);
printf("%.2f %.2f",dia,age);




	return (0);
}
