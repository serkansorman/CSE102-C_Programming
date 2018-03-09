#include <stdio.h>
#define GRIDSIZE 4


typedef enum {mined,
empty,
flaggedMined,
flaggedEmpty,
closedEmpty,
closedMined
}cell;



/*Functions prototypes */

void printGrid (cell grid[][GRIDSIZE]);	/* Prints game board */

int openCell(cell grid[][GRIDSIZE], int x, int y); /* Opens the  cell according to the coordinates entered by the user */

void flagCell(cell grid[][GRIDSIZE], int x, int y); /* Flag or unflag the selected cell */

int isCellEmpty(cell grid[][GRIDSIZE], int x, int y); /* Checks whether the cell is empty or not */

int isLocationLegal(int x, int y); /* Checks whether the entered coordinates are in grid or not */

void initGrid(cell grid[][GRIDSIZE]); /* Create matrix as an arbitrary initial game board with closed-empty and closed-mined cells.*/

int asMain(); /* Takes player's choice, to count their moves, and to call functions according to the player's wish. */




/* Create matrix as an arbitrary initial game board with closed-empty and closed-mined cells.*/
void initGrid(cell grid[][GRIDSIZE])
{
	int i,j;

	cell myBoard[GRIDSIZE][GRIDSIZE] = 
	{
		{closedEmpty,closedMined,closedMined,closedEmpty},
		{closedEmpty,closedEmpty,closedMined,closedMined},
		{closedEmpty,closedEmpty,closedEmpty,closedEmpty},
		{closedEmpty,closedEmpty,closedEmpty,closedEmpty}
	};

	for(i=0;i<GRIDSIZE;i++)         /* Assign the elements of "myBoard" to "grid" */
		for(j=0;j<GRIDSIZE;j++)
			grid[i][j] = myBoard[i][j];
}

void printGrid(cell grid[][GRIDSIZE]) /* Takes grid from asMain and prints game board */
{
		int i,j;
		
		
		for (i=0; i<GRIDSIZE; i++)					/*Check the grid and prints elements according to enumtype */
		{
			for (j=0; j<GRIDSIZE; j++)	
			{	
				if(grid[i][j] == flaggedMined || grid[i][j] == flaggedEmpty)    
					printf("%c ",'f');                                          /* "f" represents flagged cells */
				if(grid[i][j] == closedMined || grid[i][j] == closedEmpty)      
					printf("%c ",'.');                                          /* "." represents closed cells */
				if(grid[i][j] == empty)
					printf("%c ",'e');                                          /* "e" represents empty cells that have been opened */
			}
			printf("\n");
			printf("\n");
		}
		
}


/* Checks whether the entered coordinates are in grid or not according to GRIDSIZE*/
int isLocationLegal(int x, int y) 
{
	int result;
	
	if(x < GRIDSIZE && x >= 0 && y >= 0 && y < GRIDSIZE)
		result = 1;											/* return 1,if location is legal */
	else	
		result = 0;											/* return 0,if location is illegal */
	return result;
}


/* Opens the  cell according to the coordinates entered by the user */
int openCell(cell grid[][GRIDSIZE], int x, int y)
{
	int i = 1,j,result = 0,openedCells = 0;
	

	if(isLocationLegal(x,y) == 1)	/* Opens cell,if it is legal and not flagged */
	{
		if(grid[x][y] == closedEmpty && (grid[x][y] != flaggedEmpty || grid[x][y] != flaggedMined))
		{
			/*8 neighbors will be checked for emptiness and empty neighbors are also opened; 
			  each neighbor's 8 neighbors will also be checked and opened recursively */
			if(grid[x][y] == closedEmpty && isLocationLegal(x,y) == 1 && grid[x][y] != flaggedEmpty)					
			{		
				grid[x][y] = empty;

				openCell(grid, x+i, y);			
				openCell(grid, x-i, y);
				openCell(grid, x, y+i);
				openCell(grid, x, y-i);	
			}		
		}

		for(i=0;i < GRIDSIZE;i++)		/*Counts opened cells at each stage of the game*/
		{
			for(j=0 ;j<GRIDSIZE;j++)
			{
				if(grid[i][j] == empty)
					openedCells += 1;
			}		
		}			

		result = openedCells;

		if(grid[x][y] == closedMined)	/* If a closed mined cell is chosen to open; the game will be terminated */
			result = -1;		/* return -1,if selected cell is closedMined */
	}

	return result;
	
}


int isCellEmpty(cell grid[][GRIDSIZE], int x, int y) /* Checks whether the cell is empty or not */
{
	int result;
	
	if(grid[x][y] == closedEmpty)
		result = 1;			/* return 1,if selected cell is empty. return 0 otherwise*/
	else
		result = 0;	
	
	return result;
}

void flagCell(cell grid[][GRIDSIZE], int x, int y) /* Flag or unflag the selected cell */
{
	
	if(grid[x][y] == closedEmpty && isLocationLegal(x,y) == 1) /* Process of flagging selected empty cell */
		grid[x][y] = flaggedEmpty;						
	else if(grid[x][y]== closedMined  && isLocationLegal(x,y) == 1)	/* Process of flagging selected mined cell */
		grid[x][y] = flaggedMined;						
	else if(grid[x][y] == flaggedEmpty )		        /* Process of un-flagging selected flagged cell */	
		grid[x][y] = closedEmpty;							
	else if(grid[x][y] == flaggedMined)
		grid[x][y] = closedMined;	
}

int asMain()
{
	int select,i,j,closedCells;
	int x = GRIDSIZE,y = GRIDSIZE,countMove = 0,countMine = 0,openedCells = 0,continueGame= 1;
	
	cell grid[GRIDSIZE][GRIDSIZE];
		
	initGrid(grid);
	
	for(i=0;i < GRIDSIZE;i++)					/*  Calculate the number of mine in grid */
	{
		for(j=0 ;j<GRIDSIZE;j++)
		{
			if(grid[i][j] == closedMined)
				countMine += 1;
		}		
	}		
				
				
	do {	
			for(i=0;i < GRIDSIZE;i++)		/*Counts opened cells at each stage of the game*/
			{
				for(j=0 ;j<GRIDSIZE;j++)
				{
					if(grid[i][j] == empty)	
						openedCells += 1;
					
				}		
			}			
			
			closedCells = (GRIDSIZE * GRIDSIZE) - openedCells;	/*Calculate number of remaining closed cells for terminating the game */
			openedCells = 0;		
										
			printGrid(grid);		/* Prints the current game board */
		
			/* Continue game as long as number of closed cells more than number of mine */
			if(closedCells > countMine)
			{	
				printf("1)Open Box\n2)Flagg or un-Flagg\nWhat do you want: "); scanf("%d",&select);
				switch(select)
				{
					case 1:
						printf("Enter a coordinate x: "); scanf("%d",&x);	/* Takes input to open a cell */
						printf("Enter a coordinate y: "); scanf("%d",&y);
						countMove ++;										    /*Calculate number of move */
						break;
					
					case 2:
						printf("Enter a coordinate x: "); scanf("%d",&i);	/* Takes input for flagging or unflagging the cell */
						printf("Enter a coordinate y: "); scanf("%d",&j);
						flagCell(grid,i,j);
						countMove ++;											/* Calculate number of moves */
						break;
						
					default:
						printf("Please select 1 or 2\n");
						continueGame = 0; 						/* Finishes the game due to wrong choice */
				}
			}		
			
		}while ((isLocationLegal(x,y) == 1 || isLocationLegal(i,j) == 1) && openCell(grid, x, y) != -1 && closedCells > countMine && continueGame == 1);

	if(continueGame == 1)
	{	
		/*If all empty cells are found; the game will be terminated by a win message*/
		if(openCell(grid, x, y) != -1 && isLocationLegal(x,y) == 1  )
			printf("Congratulations! You win the game with %d moves. \n",countMove);
		/*If a closed_mined cell is chosen to open; the game will be terminated by a loose message.*/
		else if(openCell(grid, x, y) == -1 && isLocationLegal(x,y) == 1)
			printf("You find the mine.Game over!!\n");
		/* If the user enters an illegal location,see this message */
		else
			printf("Coordinate is not in grid.\n");
	}	
	
	return countMove;
}
int main()
{

	asMain();
	
	return 0;


}
