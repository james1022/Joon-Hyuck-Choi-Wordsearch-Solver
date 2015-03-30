/*
 * Homework3, 600.120 Spring 2015
 * README.txt
 * Name: Joon Hyuck Choi
 * Date: Feb 25, 2015
 * Assignment 3
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 19:01 02/25/2015
 */
==========================================================
The .zip file includes:

     1) wordSearch.h
     2) wordSearch.c
     3) hw3.c
     4) testWordSearch.c
     5) Makefile
     6) README.txt
     7) grid1.txt ~ grid6.txt

==========================================================

How to compile testWordSearch:
       (Using Makefile): make testWordSearch
       (On command line): gcc -std=c99 -Wall -Wextra -pedantic -o testWordSearch -O testWordSearch.c

==========================================================

How to run testWordSearch:
       (Using Makefile): make test
       (On command line): ./testWordSearch

==========================================================

How to compile hw3:
       (Using Makefile): make wordSearch.o
       	      		 make hw3.o
			 make hw3 (or even typing make hw3 from the beginning will work as well)
       (On command line): gcc -std=c99 -Wall -Wextra -pedantic -o hw3 -O wordSearch.h wordSearch.c hw3.c

==========================================================

How to run hw3:
       (On command line): ./hw3 <textfilename>.txt
       	   and then input words that must be searched.
	   When the user wants to stop inputting words and see the result,
	   press ctrl+d.

==========================================================

Comments:

   testWordSearch.c
	Without "#include"ing "wordSearch.c" in the test driver, 
	I just copied and pasted exactly the same functions into the file 
	to make it easier to see the insides of the functions.
	Then, it would be easier to look through the original functions to 
	write thorough test cases.

   Inside the zip file, I included a few sample grid text files that I used to test.
   grid1.txt through grid3.txt are valid grids, and grid4.txt through grid6.txt are invalid.

==========================================================

Plan for HW3 already submitted on Blackboard copied and pasted here again:

Plan:

1. For an imagniary sample input grid file, write up a flow of how the program will run.
-> Write each step specifically!
run hw3 (with a grid file.txt as command input) --> read the grid file to check for errors
--> take user input for a list of words to search for --> use an array of pointers to dynamically
allocate space for each char array (string) --> With that in hand, use qsort to sort the word list 
(don't switch the actual words but just make the pointers in the array of pointers keep changing)
--> after the word list is sorted, read the grid file again and store the chars in a 2D array
--> loop through each possible combination of chars and for each of those combinations, check if it
matches with any of the words in the sorted word list. Since the list is sorted, it would be easy
to just use binary search to make things quicker --> if the combination is in the list, output the
position and direction; if it's not in the list, don't do anything --> loop until the end --> end 

2. In each step of that flow, write out what functions will be needed.
-> Write function name to imply its purpose.
<List of potentially useful functions>
void readGrid(FILE* fp); //just reads the grid to check for errors
void writeGrid(FILE*fp, char[][] grid); //write the chars fromt the file to an empty 2D char array
char* makeList(); //reads in from user input of words to search for and makes the list (unsorted) 
--> need to think about this more
qsort(); //already defined in <stdlib.h>	
bool binarySearch(char* combo, char* list[]); //looks for *combo in *list[] and returns T or F

3. List those functions in a header file.

4. Write up a sketch of the header file that will contains those functions.

5. Think more about what return types and argument types will be needed for those functions.

6. Define the fuctions in a .c file with the same name as the .h file.

7. Write a tester driver to test the functions.
-> Use assert() statements
-> Write a command in Makefile

8. Commit the .h file and function .c file in bitbucket
-> as many times as necessary

9. Fix errors and see if anything can be improved

10. Commit again

11. Write hw3.c: first read the grid to check for errors
-> find out the number of rows and columns: save those numbers.
-> Write a command in Makefile to compile, link, and run all the relevant files

12. Take in user input of words to search for and sort the word list.
-> use quick sort and array of pointers.
-> don't try to actually move the words around but the pointers.

13. Make a 2D char grid[numRow][numCol] with the numRow and numCol obtained from step11.

14. Read the grid again and fill the 2D grid declared in step13.

15. Looping through every possible combination of chars (4 directions) in the 2D grid,
see if each instance matches with anything in the list of words to search for using binary search.

16. Output the position of the word if it exists and nothing if it doesn't.

17. Commit again

18. Keep working and fix errors

19. Commit in the process.

20. Once everything is working, see if any improvements can be made.

21. End

==========================================================
