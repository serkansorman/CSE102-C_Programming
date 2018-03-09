#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_NUM_WORDS 500
#define WORD_LENGTH 50

int getAndFilterWord(char * w); /*Changes all the alphabetical characters to lowercase and removes everything else than letters*/

void addWord(char * w, char words[MAX_NUM_WORDS][WORD_LENGTH],int occur[MAX_NUM_WORDS], int * word_count); /* Adds filtered words into the word array  and counts words*/

void sortWords(char words[MAX_NUM_WORDS][WORD_LENGTH], int occur[MAX_NUM_WORDS],int word_count);/*Sorts words  according to  their occurrences*/

void myTest(); /* Takes input from user and test the functions */


/*Changes all the alphabetical characters to lowercase and removes everything else than letters*/
int getAndFilterWord(char * w)
{	
	char dest[50];
	int x = 0,status = 1,i,len;
	
	for(i=0;i<50;i+=1)

		dest[i] = '\0';
		len = strlen(w);    /*Find the lenght of words*/

		for(i=0;i<len;i+=1)
		{
			if(w[i] >='A' && w[i] <= 'z')   /* Changes all the alphabetical characters to lowercase */
		 	{
		  		dest[x] = tolower(w[i]);
		  		x +=1;
		 	}
		}
		
		for(i=0;i<len;i+=1)             /* Rewrites the w string from the temp string */
		{
			w[i] = '\0';
			w[i] = dest[i];
		}
	
		if(strcmp(w,"") != 0 && strcmp("end",w) != 0) /* if filtered word is not NULL and "end" return 1 */
			status = 1;
		else 
			status = 0;

	return status;

}

/* Adds filtered words into the word array  and counts words*/
void addWord(char * w, char words[MAX_NUM_WORDS][WORD_LENGTH],int occur[MAX_NUM_WORDS], int * word_count)
{
	int i,control = 0;
    /* If "filtered" word was in the array only increment the word counter for its index.*/
	for(i = 0; i < *word_count ; i +=1) 
	{
		if(strcmp(words[i],w) == 0 )    /*If words array enters this  loop, it will not enter the following condition due to control variable. */
		{
			occur[i] +=1 ;
			control += 1;               /* Change the control */
		}
	}
    
    /*If a “filtered word” is not in the word array already; adds it into the word array 
      and increment the word counter by one for the same index in the word counter array*/
	if(strcmp(words[*word_count],"") == 0 && control == 0)
	{
		strcpy(words[*word_count],w);
		occur[*word_count] +=1 ;
		*word_count +=1 ;

	}

}

/*Sorts words by increasing order with respect to the number of their occurrences.*/
void sortWords(char words[MAX_NUM_WORDS][WORD_LENGTH], int occur[MAX_NUM_WORDS],int word_count)
{

   int i, j, position, tempOccur;
   char tempStr[500];

   for ( i = 0 ; i < word_count ; i++ )  
   {
      for ( j = i + 1 ; j < word_count ; j++ )
      {
         if ( occur[j] > occur[i] )  /* Compare occurrences for swapping */
         {
            tempOccur = occur[i];                  /* Swaps word's occurrences */
         	occur[i] = occur[j];
         	occur[j] = tempOccur;

         	strcpy(tempStr,words[i]);              /* Swaps words in words array*/
         	strcpy(words[i],words[j]);
         	strcpy(words[j],tempStr);
         }
      }   
   }
}
	

/* Takes input from user and test the functions */
void myTest()
{
    char w[50];
    char words[MAX_NUM_WORDS][WORD_LENGTH];
	int occur[MAX_NUM_WORDS], word_count = 0,i;

	for(i=0;i<500;i+=1)
		strcpy(words[i] , "\0");
    
	for(i=0;i<500;i+=1)
		occur[i] = 0;
    
    printf("Bir cumle giriniz: ");

    while(strcmp(w,"end") != 0) /* Takes words as input until the input line contains the word “end” */
    {
    	scanf("%s",w);
		if(getAndFilterWord(w) == 1)    /* if filtered word is not NULL ,calls the addWord funtion */
			addWord(w,words,occur,&word_count);
    }
   sortWords(words,occur,word_count);
			
   for(i=0;i< word_count;i++)           /* Shows the words, with their occurrences by increasing order*/
   {	
   		printf("%d) %s = ",i+1,words[i]);
		printf("%d\n",occur[i]);
   }
}
int main(void)
{

	myTest();

	return 0;


}
