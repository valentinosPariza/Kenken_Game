
/** @file kenken.c
 *  @brief The game of the kenken puzzle simulated with some commands.
 *
 *
 *  This file is a complete program(main,functions,...) which simulates the 
 *  game  kenken puzzle.For more information about how the game is played 
 *  @see https://en.wikipedia.org/wiki/KenKen
 *  This file includes all the operations of the game-puzzle.  
 *  In general for the game there are defined two ,two dimensional arrays
 *  -one for the values of the puzzle (in each cell) and the other for 
 *  its cage Characters(the cages which each cell belong to are represented by 
 *  letters [a-z]) size of DxD (constant D=Dimension ) - and  two of one 
 *  dimensional arrays, size of constant L (Letters=26) - one for storing the
 *  operators which are used to calculate the cage results and the other
 *  for storing the results of each cage which must have.These structures
 *  (arrays) are created in stack during the excecution of main method and 
 *  then all the methods take as parameters( the addresses of the arrays as 
 *  arguments ) these arrays and make changes on them or use them in any 
 *  way for solving a specific aspect.
 *
 *
 *  
 *  This file contains all the functions which the game kenken-puzzle
 *  will need to be simulated.In this file there are many functions
 *  each of them represents a single purpose and maintains a specific 
 *  action.All the functions and more details about the functions and 
 *  the interactions with the arrays are explained bellow.
 * 
 *  @version 1.0
 *  @author Valentinos Pariza
 *  @bug No know bugs.
 *
 */



/**
   Libraries which are included inside this file
*/
#include <stdio.h>
#include <string.h>

#define D 7    // Max dimension of the array of values and cages
#define L 26   // Max Cages ahich the program can have
#define Max_LINE_LENGTH 90          
#define MANUAL "commandsOfKenkenMANUAL.txt" // a text where the manual 
                                            // of the commands from the
                                            // command line is loaded

//constants for return values in some methods
#define FILE_PROBLEMS -1         
#define ILEGAL_COORDINATIONS 1   // if (row,column) is ilegal
#define ILEGAL_ACTION_DEL -2     // delete action is ilegal on an element
#define ILEGAL_ACTION_INS -3     // insert action is ilegal on an element
#define ILEGAL_VALUE 3           // value inserted to array is ilegal
#define ILEGAL_DIMENSION 2       // dimension which was given is ilegal
#define INCORRECT_PUZZLE_READ 4  // the puzzle which was created isn't  
                                 // a correct KenKen puzzle.


//Function Prototypes

void printLine(int dimension,FILE *fp);

void printManual();

void printMenu(int dimension);

int writePuzzle(short values[D][D],char cages[D][D],int dimension,char \
   fileName[]);

void printCagesBar(short results[L],char operators[L],int numCages);

void printPuzzle(short values[D][D],char cages[D][D],int dimension,FILE *fp);

int cageCharacterHasAppropriateValues(short values[D][D],char cages[D][D],\
	char operators[L],short results[L],int dimension,char cageCharacter,\
	int useForValidity);

int hasValidColumns(short values[D][D],int dimension);

int hasValidRows(short values[D][D],int dimension);

int cagesHaveAppropriateValues(short values[D][D],char cages[D][D],char \
operators[L],short results[L],int dimension,int numCages,int useForValidity);

int checkForValidityOfThePuzzleCreated(char cages[D][D],int dimension,\
int numCages);

int readPuzzle(short results[L],char operators[L],char cages[D][D],int \
   *numCages,int *dimension,char *fileName);

int deleteCell(short values[D][D],int dimension,int row,int column);

int addCell(short values[D][D],int dimension,int row,int column,short value);

int play(short values[D][D],char cages[D][D],short results[L],\
	char operators[L],int dimension,int numCages,char *filename);

int solution(short values[D][D],char cages[D][D],int row,int column,\
int dimension,short results[L],char operators[L],int numCages);

int isCorrect(short values[D][D],char cages[D][D],short results[L], \
	char operators[L],int dimension ,int numCages,int useForValidity);

int checkForValidKenkenCages(char cages[D][D],int dimension,int numCages);

int findCellsOfCage(char cages[D][D],int dimension,char checkedCages[D][D]
   ,int row,int column,char cageCharacter);


// 


/** 
 * @brief Prints a specified formatted line which is used in the puzzle array 
 *
 *  This function prints a specified formatted line which is used as a 
 *  seperator in the puzzle array(which is printed)
 *
 *  @param dimension the dimension of the general arrays where the values 
 *       are placed(in one) and the cage characters for each cell(in the other) 
 *  @param *fp a pointer to memory where the output will be directed for output
 *  @return void

 */
void printLine(int dimension,FILE *fp)
{
			for(int i=0;i<dimension;i++)
			{
					fprintf(fp,"+------");
		
			}

			fprintf(fp,"+\n");		
	
}



/** @brief Prints all the cells in the array detailed.
 *
 *  This function prints the cells of the array with all the cells 
 *  showing the characters' cages and their values.
 *
 *  @param values a two dimensional array where the arithmetic values 
 *           of each cell are placed
 *
 *  @param cages a two dimensional array where the  cage's characters of each 
 *          cell are placed
 *
 *  @param dimension the dimension of the general arrays where the values 
 *       are placed(in one) and the cage characters for each cell(in the other) 
 *
 *  @param *fp a pointer to memory where the output willi be directed for output
 *  @return void
 */
void printPuzzle(short values[D][D],char cages[D][D],int dimension,FILE *fp)
	{
			
			printLine(dimension,fp);
			
			for(int i=0;i<dimension;i++)
			  {
					

					for(int j=0;j<dimension;j++)
						{
							fprintf(fp,"|  %d%c  ",values[i][j],cages[i][j]);
						
						}
						
						fprintf(fp,"|\n");
						
					printLine(dimension,fp);

			  }	

	}



/** 
 * @brief Prints the cage bar of the program.
 *
 *  This function prints a cage bar (array formatted) which has all the
 *  cage characters-teams with the corresponding results by a specific
 *  evaluation.
 *
 *  @param results One dimensional array which has the results which each cage
 *  must evaluate by its cells.
 *
 *  @param operators One dimensional array which has the operators which each 
 *  cage must use on the cells for calculating a result.
 *
 *  @param numCages The number of the different cages which exist in the array.
 *  @return void
 */
void printCagesBar(short results[L],char operators[L],int numCages)
{

			char c='a';

		for(int i=0;i<numCages;i++)
		{

			printf("%c=%d%c ",c++,results[i],operators[i]);

		}

		printf("\n");

 }



  /** 
 *  @brief This function prints to a file the puzzle array which has been 
 *  created so far. 
 *
 *  This function writes to a file indicated by the parameter fileName[]
 *  the game puzzle array using the method @see  printPuzzle(short values[D][D],
 *  char cages[D][D],int dimension,FILE *fp).
 *
 *  @param values a two dimensional array where the arithmetic values 
 *           of each cell are placed
 *
 *  @param cages a two dimensional array where the  cage's characters of each 
 *          cell are placed
 *
 *  @param dimension the dimension of the general arrays where the values 
 *       are placed(in one) and the cage characters for each cell(in the other) 
 *
 *  @param fileName[] One dimensional array which has a String of a file name
 *         which will be used to write in it.
 *  @return void
 */
  int writePuzzle(short values[D][D],char cages[D][D],int dimension,char \
  fileName[])
  {
			
				FILE *fp;

				fp=fopen(fileName,"w");
		
				if(fp==NULL)
					return FILE_PROBLEMS;
			
			
		printPuzzle(values, cages,dimension,fp);
									

				fclose(fp);

		return 0;

  }




 /** 
 *  @brief Prints a manual on how using the command through the kenken program
 *
 *  This function prints out a manual text ,which helps the user to understand
 *  what operations can be made from the command line through the program.
 *  The manual text is located in a text file.When this function is invoked
 *  then the text file from the secondary memory is read and displayed on the 
 *  screen.
 *  
 *  @return void
 */
   void printManual()
   {

   printf("\n");

   FILE* fp=NULL;   
    
   fp=fopen(MANUAL,"r");   // constant which u

    if(fp==NULL)
   {
      printf("There is no available manual.\n\n");
      return ;
   
   }


   char line[Max_LINE_LENGTH];

   while(fgets(line,sizeof(line),fp)!=NULL)
   {

      printf("%s",line);
     
    }

      fclose(fp);
      
      printf("\n");

   }



/** 
 *  @brief Prints a menu on the screen where all the options are showed.
 *
 *  This function prints out a menu which shows the options that the user will
 *  have in play mode (excecuting the program with option "-i").
 *  
 *  @param dimension the dimension of the general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other)
 *  
 *  @return void
 */
void printMenu(int dimension)
  {
		
		printf("Enter your command in the following format :\n");
		printf(">i,j=val: for entering val at position (i,j)\n");
		printf(">i,j=0  : for clearing cell (i,j)\n");
      printf(">0,0=0  : for saving and ending the game\n");
		printf("Notice  : i,j,val numbering is from [1..%d]\n",dimension);
		printf("> ");

  }




 /** 
 *  @brief Checks whether the puzzle has valid columns and returns the result
 *
 *  This function checks each column of the array-puzzle(with values) 
 *  in order to ascertain whether the array has a valid column or not.
 *  A valid column is a column which where all its cells' values are not 
 *  the same except if their values are zero(indicating that it doesn't 
 *  have in it any value).  
 *
 *  
 *  @param values A two dimensional array where the arithmetic values 
 *           of each cell are placed 
 *
 *  @param dimension The dimension of the two general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other)
 *  
 *  @return 1 if the array-values has valid columns or 0 if not
 */
 int hasValidColumns(short values[D][D],int dimension)
	 {

	int r=0,c=0,q=0;

		for(c=0;c<dimension;c++)      
		 {
				for(r=0;r<dimension;r++)
				{

               if(values[r][c]!=0) // if the cell is 0(doesn't have a value)
               {                   // we skip it

                  for( q=r+1;q<dimension;q++)   // we check all the rest 
						{                             // cells if have the same
                                                // value(duplicate cells on
                                                // column   )
   
								if( (q!=r) && (values[r][c]==values[q][c]) )
										return 0;
						}

               }
					 
				 }

 		  }


		return 1;	

  }




/** 
 *  @brief Checks whether the puzzle has valid rows and returns the result
 *
 *  This function checks each row of the array-puzzle(with values) 
 *  in order to ascertain whether the array has a valid row or not.
 *  A valid row is a row which where all its cells' values are not 
 *  the same except if their values are zero(indicating that it doesn't 
 *  have in it any value).  
 *
 *  
 *  @param values a Two dimensional array where the arithmetic values 
 *           of each cell are placed 
 *
 *  @param dimension The dimension of the two general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other).
 *  
 *  @return 1 if the array-values has valid rows or 0 if not
 */
int hasValidRows(short values[D][D],int dimension)
	 {

	int r=0,c=0,q=0;

		for(r=0;r<dimension-1;r++)
		 {
				for(c=0;c<dimension;c++)
				{
      
               if(values[r][c]!=0)  // if the cell is 0(doesn't have a value)
               {                    // we skip it

                for( q=c+1;q<dimension;q++)      // we check all the rest 
						{                             // cells if have the same
                                                // value(duplicate cells on
                                                // row   )
						
								if( (q!=c) && (values[r][c]==values[r][q]) )
										return 0;
		          	}

               }
                     
				 }

 		  }


		return 1;	

    }





/** 
 *  @brief Checks whether the cells of a cage are valid or not.
 *
 *  This function checks whether the cells of a cage (cageCharacter) have
 *  valid values or not.Valid values for cages are the values which if
 *  they sumed up or multiplied (it depends by the operation which the cage
 *  indicates ) together they get a result that is equal with the predefined
 *  result(array result).Also this method can be used for verifying if a cage
 *  is valid for an actual solution (useForValidity=0) or if a cage is 
 *  valid because all the values inserted in the cells of the cage ,so far are 
 *  following the rules of the game(it might not indicate that there is a 
 *  solution - if there are cells where no values have been inserted).
 *  You can see also @see cagesHaveAppropriateValues(short values[D][D],
 *  char cages[D][D],char operators[L],short results[L],int dimension,
 *  int numCages,int useForValidity)
 *
 *  
 *  @param values a Two dimensional array where the arithmetic values 
 *           of each cell are placed 
 *
 *
 * @param cages A two dimensional array where the  cage's characters of each 
 *          cell are placed
 *
 * @param operators One dimensional array which has the operators which each 
 *  cage must use on the cells for calculating a result
 *
 * @param results One dimensional array which has the results which each cage
 * must evaluate by its cells.
 *
 *  
 *  @param dimension The dimension of the general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other)
 *
 * @param cageCharacter a character which is used to verify the positions
 *        of the cells in the array(cages) which belong to the cage-team with
 *        character cageCharacter(cageCharacter=a cage character identifier)
 *
 * @param useForValidity It is a flag that if it is 0 then this function
 *       is used not for validity of the puzzle but for verifying if there
 *       is an actual solution for the puzzle.If it is not 0 then this function
 *       checks if the elements so far placed are following the rules of the
 *       game
 *  
 *  @return 1 if all the cells which belong to the cageCharacter cage are valid
            else returns 0
 */
int cageCharacterHasAppropriateValues(short values[D][D],char cages[D][D],\
	char operators[L],short results[L],int dimension,char cageCharacter,\
	int useForValidity)
{

	int result=0;                 // suppose that the operation of the 
	int usesMultiplication=0;     // cageCharacter cage is addition

		if(operators[(int)(cageCharacter-'a')]=='*') // if it is multiplication
			{                                         // we change and 
				result=1;                              // update the flag
				usesMultiplication=1;

			}


	// This loop is made for calculating the sum/multiplication
   // of a specific cage
	for(int i=0;i<dimension;i++)
		{
			 for(int j=0;j<dimension;j++)
				{
					if(cageCharacter==cages[i][j])  // we are interested only
						{                            // on the cells which belong
                                               // to the cage cageCharacter                                                 
   
							if(useForValidity && values[i][j]==0)//if we check only
								return 1;                           // for valid cages
                                                            // , then we   
							 if(usesMultiplication)                //ignore zeroes
									result*=values[i][j];            // else if we
                                                            // check if there     
							 else result+=values[i][j];            // is a solution
                                                            // then we include 
                  }                                         //them in the check             
						
				}
			
		}	

      // here we return whether the result that we have calculated is the 
      // same with the result that has been indicated from the begining 

		return result==results[(int)(cageCharacter-'a')];

}





/** 
 *  @brief Checks whether all the cells of the cages are valid or not.
 *
 *  This function checks whether the cells of all cages have
 *  valid values or not.Valid values for cages are the values which if
 *  they sumed up or multiplied (it depends by the operation which the cage
 *  indicates ) together they get a result that is equal with the predefined
 *  result(array result).
 * 
 *  Also this method can be used for verifying if all the cages
 *  are valid for an actual solution (useForValidity=0) or if they are 
 *  valid because all the values inserted in the cells of the cages ,so far  
 *  are following the rules of the game(it might not indicate that there is a 
 *  solution - if there are cells where no values have been inserted).
 *
 *  You can see also @see  cageCharacterHasAppropriateValues(short values[D][D]
 *  ,char cages[D][D],char operators[L],short results[L],int dimension,
 *  char cageCharacter,int useForValidity);
 *
 *  
 * @param values a Two dimensional array where the arithmetic values 
 *           of each cell are placed .
 *
 *
 * @param cages A two dimensional array where the  cage's characters of each 
 *          cell are placed.
 *
 * @param operators One dimensional array which has the operators which each 
 *  cage must use on the cells for calculating a result
 *
 * @param results One dimensional array which has the results which each cage
 * must evaluate by its cells.
 *
 *  
 *  @param dimension The dimension of the general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other)
 *
 * @param numCages The number of the different cages which exist in the array.
 *
 * @param useForValidity It is a flag that if it is 0 then this function
 *       is used not for validity of the puzzle but for verifying if there
 *       is an actual solution for the puzzle.If it is not 0 then this function
 *       checks if the elements so far placed are following the rules of the
 *       game
 *  
 *  @return 1 if all the cells of all the cages are valid else returns 0
 */
int cagesHaveAppropriateValues(short values[D][D],char cages[D][D],char \
operators[L],short results[L],int dimension,int numCages,int useForValidity)
{

			char cageCharacter='a';		

			for(int i=0;i<numCages;i++)
			{
				if( !cageCharacterHasAppropriateValues( values,cages, operators,
				results, dimension,(char)(cageCharacter++),useForValidity ) )
					return 0;
			 }


			return 1;

}






/** 
 *  @brief Checks whether all the cells belong to a valid cell.
 *
 * 
 *  
 *  @param cages A two dimensional array where the  cage's characters of each 
 *        cell are placed.
 *
 *  @param dimension The dimension of the two general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other).
 *  
 * @param numCages The number of the different cages which exist in the array.
 *
 *  @return 1 if the cells belong to valid cages ,else 0          
 */
int checkForValidityOfThePuzzleCreated(char cages[D][D],int dimension,\
int numCages)
    {

         for(int i=0;i<dimension;i++)
            {
                for(int j=0;j<dimension;j++)
                  {
                     if( (cages[i][j]<'a' || cages[i][j]>('a'-1+numCages))) 
                        return 0;                 
      
                  }

            }

      return 1;

     }




/** 
 *  @brief Checks whether the puzzle is valid-correct or not.
 *
 *
 * This function checks whether the puzzle is solved(if useForValidity=0) or
 * if it is valid with the values inserted to it so far(useForValidity=1)
 * and returns the result.
 *
 * For this function see also :
 * a) cagesHaveAppropriateValues(short values[D][D],char cages[D][D],char 
 *   operators[L],short results[L],int dimension,int numCages,int
 *   useForValidity)
 * b)hasValidRows(short values[D][D],int dimension)
 * c)hasValidColumns(short values[D][D],int dimension)
 *  
 * @param values a Two dimensional array where the arithmetic values 
 *           of each cell are placed 
 *
 * @param cages A two dimensional array where the  cage's characters of each 
 *          cell are placed
 *
 * @param results One dimensional array which has the results which each cage
 * must evaluate by its cells.
 *
 * @param operators One dimensional array which has the operators which each 
 *  cage must use on the cells for calculating a result
 *  
 * @param dimension The dimension of the general arrays where the values 
 * are placed(in one) and the cage characters for each cell(in the other)
 *
 * @param numCages The number of the different cages which exist in the array.
 *
 * @param useForValidity It is a flag that if it is 0 then this function
 *       is used not for Validity of the puzzle but for verifying if there
 *       is an actual solution for the puzzle.If it is not 0 then this function
 *       checks if the elements so far placed are following the rules of the
 *       game
 *  
 *  @return 1 if the puzzle is valid-solved or 0 if not
 */
int isCorrect(short values[D][D],char cages[D][D],short results[L],\
	char operators[L],int dimension ,int numCages,int useForValidity)
	{

			if(!hasValidRows(values,dimension))
					return 0;


			if(!hasValidColumns(values,dimension))
					return 0;

			
			return cagesHaveAppropriateValues(values,cages,operators,results\
				, dimension, numCages,useForValidity);
			 

   }




/** 
 *  @brief Tries to insert a new value in a cell in the puzzle
 *
 *  This function tries to insert a value in a cell and returns a status
 *  of what happened.
 *
 *  
 *  @param values a Two dimensional array where the arithmetic values 
 *           of each cell are placed 
 *
 *  @param dimension The dimension of the two general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other).
 *
 *  @param the row in the array which the value is trying to be placed[1-D]
 *
 *  @param the column in the array which the value is trying to be placed[1-D]  
 *
 *  @return ILEGAL_COORDINATIONS if the combination of row and column is 
 *          not a valid cell in the puzzle
 *          ILEGAL_ACTION_INS if the insertion is made on a not empty cell
 *          ILEGAL_VALUE if the value trying to be placed is not valid[1-D]
 *          O if the the insertion was succesful
 */
int addCell(short values[D][D],int dimension,int row,int column,short value)
{
		if( (row<1 || row>dimension) || (column<1 || column>dimension) )
			return ILEGAL_COORDINATIONS;		

		if(values[row-1][column-1]!=0)
			return ILEGAL_ACTION_INS;

			if(value<1 || value>dimension)
				return ILEGAL_VALUE;		

		values[row-1][column-1]=value;

		return 0;
}



/** 
 *  @brief Tries to delete a value from a cell in the puzzle
 *
 *  This function tries to delete a value from a cell and returns a status
 *  of what happened.
 *
 *  
 *  @param values a Two dimensional array where the arithmetic values 
 *           of each cell are placed 
 *
 *  @param dimension The dimension of the two general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other).
 *
 *  @param the row in the array which the value is trying to be placed[1-D]
 *
 *  @param the column in the array which the value is trying to be placed[1-D]  
 *
 *  @return ILEGAL_COORDINATIONS if the combination of row and column is 
 *          not a valid cell in the puzzle
 *          ILEGAL_ACTION_DEL if the delete operation is made on an empty cell
 *          O if the the insertion was succesful
 */
int deleteCell(short values[D][D],int dimension,int row,int column)
{
		if( (row<1 || row>dimension) || (column<1 || column>dimension) )
			return ILEGAL_COORDINATIONS;		
   
   
		if(values[row-1][column-1]==0)
			return ILEGAL_ACTION_DEL;
      
         

		values[row-1][column-1]=0;

		return 0;
}




/** 
 *  @brief Reads a puzzle from a file and updates the structures-arrays.
 *
 *  This function read from a file the data to build the game-puzzle and
 *  checks whether the input data from the file can build a logically valid
 *  kenken game-puzzle (It doesn't check whether the game which is loaded has
 *  a solution or not).
 * 
 *  This function checks for the Validity of the puzzle created with :
 *  a)checkForValidKenkenCages(char cages[D][D],int dimension,int numCages)
 *  b)checkForValidityOfThePuzzleCreated(char cages[D][D],int dimension,\
 *   int numCages)
 * 
 *  @param results One dimensional array which has the results which each cage
 *  must evaluate by its cells.
 *
 *  @param operators One dimensional array which has the operators which each 
 *  cage must use on the cells for calculating a result
 *
 *  @param cages A two dimensional array where the  cage's characters of each 
 *        cell are placed.
 *
 *  @param numCages The number of the different cages which exist in the array.
 *
 *  @param dimension The dimension of the two general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other).
 *  
 *  @param *filename the name of the file from which the data are read
 *
 *  @return  FILE_PROBLEMS The file could not be found or opened in order to
 *           read from it
 *           ILEGAL_DIMENSION The dimension which is indicated by the data
 *           is not in the correct rang(it must be from [1-D] where D is the 
 *           maximum)
 *           ILEGAL_COORDINATIONS Ilegal (row,column) coordination for including
 *            a cell in a cage team
 *           INCORRECT_PUZZLE_READ the puzzle which has been read isn't a
 *           correct kenken game(doesn't follow the rules of the KenKen game)
 */
int readPuzzle(short results[L],char operators[L],char cages[D][D],int\
 *numCages,int *dimension,char *fileName)
	{
	
			// Because we know the format the file must have we read in a 
         // specific way
				
			FILE *fp;
			fp=fopen(fileName,"r");
			
		
			if(fp==NULL)
				return FILE_PROBLEMS;

	
			fscanf(fp,"%d",dimension);		

			if(*dimension<=0 || *dimension>D)
				return ILEGAL_DIMENSION;

			
		
				int i=0,j=0;

		
		 while(EOF!=fscanf(fp,"%hd%c",&results[*numCages],&operators[*numCages]))
			{
				

				char line[Max_LINE_LENGTH];	// create a local array in stack to
                                          // read a line from the file
	         
				
				fgets(line,sizeof(line),fp);
					

				char *token=NULL;

            token=strtok(line," \n");   // we split the line into tokens		
				
	
				while(token!=NULL)	
				{
               
               sscanf(token,"(%d,%d)",&i,&j);  // and because we know its
                                               // format we take the 
                                               // the correctvalues from it 
		
					if( (i<1 || i>*dimension) || (j<1 || j>*dimension))
							return ILEGAL_COORDINATIONS;
         
   
					cages[i-1][j-1]='a'+*numCages; //all the characters of the cages
                                              // start from 'a' so the ith
                                              // cage is 'a'+i
					
              token=strtok(NULL," \n");  

				}	
		
				
				*numCages=1+(*numCages);
			}
			
     //check for the validity of the cells
		   int result=checkForValidityOfThePuzzleCreated(cages,*dimension,\
            *numCages);

    // check if all the cells are linked together with one common side each one
		result=(result && checkForValidKenkenCages( cages,*dimension,*numCages));

         if(result!=0)
            return 0;
          else 
            return INCORRECT_PUZZLE_READ;

	}	




/** 
 *  @brief This function simulates the play mode of the game-puzzle.
 *
 *  This function creates an interface with the user and creates a more 
 *  friendly enviroment for the user to play.It prompts the user for giving
 *  an option(all the options are displayed by the program) and tries to 
 *  excecute its options and informs the user for the change of the puzzle
 *  and for the solution of the game.
 *
 *  This function uses : 
 * a)deleteCell(short values[D][D],int dimension,int row,int column)
 * b)addCell(short values[D][D],int dimension,int row,int column,short value)
 * c)isCorrect(short values[D][D],char cages[D][D],short results[L],\
 * char operators[L],int dimension ,int numCages,int useForValidity)
 * d)writePuzzle(short values[D][D],char cages[D][D],int dimension,char \
 *  fileName[])
 *
 * 
 *  @param values A two dimensional array where the arithmetic values 
 *           of each cell are placed 
 *
 *  @param cages A two dimensional array where the  cage's characters of each 
 *        cell are placed.
 *
 *  @param results One dimensional array which has the results which each cage
 *  must evaluate by its cells.
 *
 *  @param operators One dimensional array which has the operators which each 
 *  cage must use on the cells for calculating a result
 *
 *  @param dimension The dimension of the two general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other).
 *
 *  @param numCages The number of the different cages which exist in the array.
 *  
 *  @param *filename the name of the file which were read all the data of the 
 *      puzzle and it will be used for creating a new name of file and a new
 *      file in which the snapshot of the game-puzzle might be saved if the
 *      appropriate option is given
 *
 *  @return  0 indicating that everything is handled inside smoothly
 */
int play(short values[D][D],char cages[D][D],short results[L], \
 char operators[L],int dimension,int numCages,char *filename)
  {
			printCagesBar(results,operators,numCages);
         printf("\n");

         int endTheGame=0;
			int gameSolved=0;

			int row=0,column=0,value=0;

			do{
					printPuzzle(values,cages, dimension,stdout);
					printMenu(dimension);

					if(scanf("%d,%d=%d",&row,&column,&value)!=3)
					{
						while(getchar()!='\n');
						printf("\nWrong format of the command.\n");
					}
					else
					{
                     printf("\n");
						int statusCommand=0;       // status which shows if the
			                                    // option of the user was valid

                   
						if(value!=0)  // check if it is the option a,b=value
						{             // where a,b can be anything but value!=0 

							 statusCommand=addCell(values,dimension,row,column,value);
							
						}
						else if(row!=0 || column!=0)         
						{						  // check if it is the option a,b=0  
                                      // where a,b can be anything but value==0
         
							statusCommand=deleteCell( values,dimension,row,column);
						}
						else  
						{     // This is the option where 0,0=0 (necessarily)


                        // create a name of a file in order to write 
                        // the snapshot of the file inside it
							char newFileName[strlen(filename)+5];

							strcpy(newFileName,"out-");  //['o','u','t','-',...]

							strcat(newFileName,filename);
                     // ['o','u','t','-',filename]

							if(writePuzzle(values,cages,dimension,newFileName)==0 )
								{
														
									printf("\nThe game was saved in the file %s.",\
											newFileName);
                                 
									   
								}
								else
									{
										printf("\nGame couldn't be saved in file %s",\
										newFileName);
									}

								printf("\nExiting the game.");
								endTheGame=1;           
                           // indicate that the game is over
                           // Exiting the game											

						}
					
						
						
                   if(!endTheGame)
                  {
      
                        // Check what is happened with the excecution of the
                        // option-cmmand of the user
							switch(statusCommand)
							{
                        case 0 : printf("Value inserted!");
                                    break;

                        case ILEGAL_VALUE : 
                                    printf("Error : Ilegal value isertion!");
                                    break;
                  
                        case ILEGAL_COORDINATIONS : 
                                 printf("Error : ilegal combination of "
                                        "(row,column) for coordination.");
                                    break;
   
                        case ILEGAL_ACTION_INS : 
                                    printf("Error : You have to delete first"
                                          " an element to add a new one!");
                                    break;

                         case ILEGAL_ACTION_DEL : 
                                       printf("Error : The element you have "
                                       "tried to delete has already been"
                                       " deleted!");
                                    break;
         
                        default : printf("Couldn't understant your command!");
                                    break;
					   	}

                     printf("\n");
							
												

							gameSolved=isCorrect( values, cages, results,\
	 						operators, dimension , numCages, 0);

							if(gameSolved)
									{

                           printf("\n***Game solved***\n");
                           printPuzzle(values,cages, dimension,stdout);
                           printf("\n");
         
                            }
							else
								printf("\n***This is not a valid kenken puzzle***\n");
							
	
						}
					}


				}while(!gameSolved && !endTheGame);
		
      return 0;
		
  }





/** 
 *  @brief This function checks whether the puzzle has a solution and finds it.
 *
 *  This function is a recursive function which uses the method of brute-force
 *  for solving the game-puzzle if there is a solution.Brute force method
 *  examines every possible number (which that number follows the rules of the
 *  KenKen game) for each cell of the array until it finds the combination of 
 *  numbers in each cell which solves the puzzle.If it doesn't find a solution
 *  it returns 0,indicating that this puzzle doesn't have a solution.
 *
 *  This function uses : 
 *  a)isCorrect(short values[D][D],char cages[D][D],short results[L],\
 *  char operators[L],int dimension ,int numCages,int useForValidity)
 *
 * 
 *  @param values A two dimensional array where the arithmetic values 
 *           of each cell are placed 
 *
 *  @param cages A two dimensional array where the  cage's characters of each 
 *        cell are placed.
 *
 *  @param row The row of the array-puzzle where the program examines
 *         for valid values
 *
 *  @param column The column of the array-puzzle where the program examines
 *         for valid values
 *
 *  @param dimension The dimension of the two general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other).
 *
 *  @param results One dimensional array which has the results which each cage
 *  must evaluate by its cells.
 *
 *  @param operators One dimensional array which has the operators which each 
 *  cage must use on the cells for calculating a result
 *
 *
 *  @param numCages The number of the different cages which exist in the array.
 *  
 *
 *  @return  0 indicating that the puzzle doesn't have a solution and 1
 *           that it has
 */
int solution(short values[D][D],char cages[D][D],int row,int column,\
int dimension,short results[L],char operators[L],int numCages)
{
	 
	int i=1;   //the number which is assigned to the cell in each iteration

	while(i<=dimension)
	{
			
		values[row][column]=	i;	
	
			int flag=isCorrect(values, cages,results,operators, dimension , \
            numCages,1);

         //Examine if everything is fine so far (rows ,columns,results)



		if(flag!=0)  //  if the values inserted so far are following the rules,
		{            //  the program will check the next cell with numbers 
                   //  for validity
		          
			int result=0;
			
			int newColumn=column+1;    // every time we move to the next cell
			int newRow=row;			
	
			if(newColumn>=dimension)
			{
				newRow=row+1;           // if moved further than the columns 
				newColumn=0;            // change line
               
           if(newRow>=dimension)    
				return isCorrect( values, cages, results,operators, dimension \
                  ,numCages,0);          
            
            // if we have moved through all rows,it means that we have 
            // arrived at the end and the last check for a solution
            // is the answer if there is a solution

			}					


			result=solution(values,cages,newRow,newColumn,dimension,results, \
			operators,numCages);
						  
							if(result!=0)
							return 1;	
			
		}
      
			
		i++;
	 }

      // if in all iterations we haven't found a valid number for this cell
      // we move back to the previous to change its valuee to the next available
      // or to go further back to the next available number for the previous 
      //  cells, if there exists

   values[row][column]=	0;	
	return 0;

}




/** 
 *  @brief This function counts how many linked cells belong to common 
 *         cage and also updates an array which shows which cells have been 
 *         examined.
 *
 *  This function is a recursive function which expands in all valid
 *  directions in the array recursively in order to count how many linked 
 *  cells of the same cage exist in the array.linked cells with the rules
 *  of this game are the cells with one or more common sides.This function also
 *  gets a two dimensional array-checkedCages and marks all the cells that 
 *  have been examined.The changes on the array checkedCages are left with all
 *  the changes on it.
 *
 * 
 *
 *  @param cages A two dimensional array where the  cage's characters of each 
 *        cell are placed.
 *
 *
 *  @param dimension The dimension of the two general arrays where the values 
 *  are placed(in one) and the cage characters for each cell(in the other).
 *
 *  @param checkedCages Two dimensional array which is one-to-one array with
 *          the array with the cage characters(cages) and it is used to 
 *          mark the cage cells which have been included in the calculation
 *
 *
 *  @param row The row of the array-puzzle where the program examines
 *         for linked cage characters
 *
 *  @param column The column of the array-puzzle where the program examines
 *         for linked cage characters
 *  
 * @param cageCharacter a character which is used to verify the positions
 *        of the cells in the array(cages) which belong to the cage-team with
 *        character cageCharacter(cageCharacter=a cage character identifier)
 *
 *  @return  the number of linked characters(characters in array which 
 *  have a common side) found around the character at (row,column) 
 *
 */
   int findCellsOfCage(char cages[D][D],int dimension,char checkedCages[D][D]
   ,int row,int column,char cageCharacter)
   {

      // check whether the cell isn't marked as examined and the cell
      //  that is examined now belongs to the cage with character cageCharacter
 
      if(checkedCages[row][column]!='0' || cageCharacter!=cages[row][column])
         return 0;
      
      checkedCages[row][column]=cageCharacter;

      int result=1;
   
      if(column+1<dimension) //expand rightwards
         result += findCellsOfCage(cages,dimension,checkedCages, row, \
            column+1,  cageCharacter);
      
      
   
      if(column-1>=0) //expand leftwards
         result += findCellsOfCage(cages,dimension, checkedCages,row, \
         column-1,  cageCharacter);


      if(row-1>=0)  // expand downwards
         result += findCellsOfCage(cages,dimension, checkedCages,row-1, \
         column,  cageCharacter);


       if(row+1<dimension)   //expand upwards
         result += findCellsOfCage(cages,dimension, checkedCages,\
      row+1, column, cageCharacter);


      return result;
      

   }





   /** 
 *  @brief This function checks whether the cells of each cage are linked.
 *
 *  This function checks if the cells of each cage are linked(to have 
 *   one ore more common sides).It uses the method @seeint findCellsOfCage(
 *   char cages[D][D],int dimension,char checkedCages[D][D],int row,int
 *    column,char cageCharacter)
 *
 *
 * 
 * @param cages A two dimensional array where the  cage's characters of each 
 *          cell are placed
 *
 * @param dimension The dimension of the two general arrays where the values 
 *     are placed(in one) and the cage characters for each cell(in the other)
 *
 *  @param numCages The number of the different cages which exist in the array.
 *
 *  @return  1 if all the cells of each vage are linked to one cage-team else 0.
 *
 *       
 *
 */
   int checkForValidKenkenCages(char cages[D][D],int dimension,int numCages)
   {

      char checkedCages[D][D];      // create a DxD array of char

      int i=0,j=0;

      // initialize the array in order each cell to have a value equal to '0'
      for(i=0;i<dimension;i++)      
      {
         for(j=0;j<dimension;j++)
         {
            checkedCages[i][j]='0';
         }   
           
      }

   
     char c='a';        //the first cage's symbol

      for(i=0;i<numCages;i++)       // through all the cages
      {
         int found=0;

       
         for(int row=0;row<dimension;row++)        //find the first cell which 
         {                                         // belongs to cage c+i
            for(int column=0;column<dimension;column++)
               {
                        
                  if(cages[row][column]==(char)(c+i))    // update the linked 
                     {                              //to the first cell found 
                                                    //cells in the checkedCages   
      
                        findCellsOfCage(cages,dimension, checkedCages, row, \
                         column, (char)(c+i)); 
                      
                           found=1;
                           break ;
                     }
               }

            if(found)
               break;

         }

      }

      
       for(i=0;i<dimension;i++)        // check if there is any cell left out
       {                               // That cell is the non-linked cell
            for(j=0;j<dimension;j++)   // if exists then the puzzle isn't valid.
             {
                  if(checkedCages[i][j]=='0')
                        return 0;
             }
       }      

   return 1;
   
   }





/** 
 *  @brief This function coordinates all the operations of the function.
 *
 *  This function is the main method-function of the program .Inside of it
 *  all the operations of the program are being combined in a well-formed 
 *  way to give complete functionality and to handle every undefined situation
 *  which might occur during the excecution of some operations of the program.
 *  In the main all the data structures ( arrays ) are created and then are
 *  used by all the functions to complete some specific apsects.
 *
 *
 * 
 *  @param argc The number of words in the command which was received from  
 *          command line.Strings are arrays of characters.
 *
 *  @param *argv[] An array of pointers to Strings which these Strings are 
 *          the tokens-words of the command which was received from command 
 *          line.Strings are arrays of characters. 
 *
 *  
 *
 *  @return  0 indicating that the program was excecuted without any problem
 *           any other number indicates that there was a problem during the 
 *           excecution of the main.        
 *
 */
int main(int argc,char *argv[])
{

setbuf(stdout,NULL);   

   if(!(argc==2 && (strcmp("-m",argv[1])==0) ) && !(argc==3 && \
      (strcmp("-i",argv[1])==0 || (strcmp("-s",argv[1])==0)) ) )
      {

         for(int i=0;i<argc;i++)
         printf("%s ",argv[i]);
         printf(" : command not found\n");
         printf("For a manual enter : ./kenken -m\n");
         return 0;

      }

   
      char cages[D][D];
	   short values[D][D];
	   short results[L];
	   char operators[L];
      int dimension=0;
	   int numCages=0; 



   for(int i=0;i<L;i++)
		{
			results[i]=0;
			operators[i]='0';
			}


	for(int i=0;i<D;i++)
		{
			for(int j=0;j<D;j++)
				{
				 cages[i][j]='0';
				 values[i][j]=0;					
				}	
				
		}

   if((strcmp("-m",argv[1])==0))
   {
      printManual();
      return 0;
   }

	 int status=readPuzzle( results, operators, cages, &numCages, \
         &dimension, argv[2]);

     switch (status)
      {
            case FILE_PROBLEMS :
                   printf("Error : The game couldn't loaded.\n");
                   printf("Problems in reading from the file ");
                   printf("%s.\n\n",argv[2]);
                   return 0;

            case ILEGAL_DIMENSION : 
                   printf("Error : The dimension which is specified in the ");
                   printf("file %s is not in the ",argv[2]);
                   printf("range of [1-%d].\n\n",D);
                   return 0;

            case ILEGAL_COORDINATIONS :
                   printf("Error : Ilegal values for coordinations");
                   printf(" (row,column) in the file.\n\n");
                   return 0;

            case INCORRECT_PUZZLE_READ :
                   printf("Error : The puzzle game that was loaded isn't ");
                   printf("a correct representation of a kenken puzzle.\n\n");
                   return 0;
      
            default : break;

      }


      if( (strcmp("-s",argv[1])==0) )
      {

         status= solution( values, cages, 0, 0,dimension,results, operators,\
         numCages);

        if(status!=0)
          {

            printCagesBar(results, operators, numCages);
            printPuzzle(values,cages,dimension,stdout); 
         

          }   
         else
          {
             printf("\nThis kenken puzzle doesn't have a solution!\n");
          }   
      

      }
      else if( (strcmp("-i",argv[1])==0) )
      {
      
        play( values, cages, results,operators, dimension, numCages,argv[2]);
        printf("\n");

      }
      

	return 0;
}


