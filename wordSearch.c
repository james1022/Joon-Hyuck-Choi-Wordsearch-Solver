/*
 * Homework3, 600.120 Spring 2015
 * wordSearch.c
 * Name: Joon Hyuck Choi
 * Date: Feb 27, 2015
 * Assignment 3
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 16:53 02/27/2015
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wordSearch.h"

/*
 * Reads and saves the grid that the user input from the command line.
 * Returns the number of rows that are in the grid file.
 * Returns -1 if there is something undesirable in the grid.
 */
int readGrid(FILE* infile, FILE* outfile, char ***outGrid) {

  int ch; //the character that'll be read in from the infile
  int prevNumCol = 0; //numCol from the previous row
  int numRow = 0;
  int numCol = 0;
  int initialRowSize = 10;
  int initialColSize = 10;

  //Dynamically allocate 10 rows for **outGrid
  (*outGrid) = malloc(initialRowSize * sizeof(char*));

  while((ch = fgetc(infile)) != EOF) { //while the EOF has not been reached

    if(numRow >= initialRowSize) { //condition to realloc **outGrid
      initialRowSize *= 2; //double the size
      (*outGrid) = realloc((*outGrid), initialRowSize * sizeof(char*)); //realloc original
    } //end if

    if(numCol >= initialColSize) { //condition to realloc *outGrid
      initialColSize *= 2; //double the size
      (*outGrid)[numRow] = realloc((*outGrid)[numRow], initialColSize * sizeof(char));
    } //end if
 
    if(isspace(ch)) { //if next character is a nextline,
      if(ch == '\n') {
	if(numRow != 0 && numCol == 0) { //if it is not the first row and there are no letters in it,
	  break;
        } else if(numRow != 0 && numCol != prevNumCol) { //if numRow != 0, compare the current numCol with previous.
          return -1; //return -1 to indicate error
        } //end if
	if(numRow == 0 && numCol == 0) { //if we have a new line at the first row
	  return 0;
	}
        (*outGrid)[numRow] = realloc((*outGrid)[numRow], (numCol + 1) * sizeof(char));
	prevNumCol = numCol; //save current number of columns to compare
	numCol = 0; //set number of columns back to 0
	numRow++; //increment the number of rows
      } else {
	goto here;
      }
    } else { //if ch is just a char save the char in outGrid
      if(numCol == 0) { //if this is a new row
	(*outGrid)[numRow] = malloc(initialColSize * sizeof(char));
      }
      (*outGrid)[numRow][numCol] = tolower(ch);
      fprintf(outfile, "%c", (*outGrid)[numRow][numCol]); //for testing purposes
      numCol++; //increment the number of columns
       
   } //end if-elseif-else
  here:
    continue;
  } //end while
  (*outGrid) = realloc((*outGrid), numRow * sizeof(char*)); //realloc original

  return numRow; //return the number of rows(lines) in the grid text file
} //end readGrid()

/*
 * Similar functionality with the function readGrid(), but this function
 * returns the number of columns in the grid text file.
 */
int returnColNum(FILE* infile) {

  int ch; //the character that'll be read in from the infile
  int numCol = 0;

  while((ch = fgetc(infile)) != EOF) { //while the EOF has not been reached
    if(ch == '\n') { //if next character is a nextline,
      return numCol;
    } else { //if ch is just a char
      numCol++; //increment the number of columns       
   } //end if-elseif-else
  } //end while

  return numCol; //return the number of rows(lines) in the grid text file
} //end returnColNum()

/*
 * Helper function for qsort().
 */
int compare(const void *a, const void *b) {
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
} //end compare()

/*
 * Takes in the sorted list of words and searches for the target word.
 */
bool binarySearch(char **wordList, int max, char *target) {

  int position;
  int begin = 0;
  int end = max - 1;
  int cond = 0;

  while(begin <= end) {
    position = (begin + end) / 2;
    if((cond = strcmp(wordList[position], target)) == 0) {
      return true;
    } else if (cond < 0) {
      begin = position + 1;
    } else {
      end = position - 1;
    }
  } //end while
  return false;
} //end binarySearch()

/*
 * Loops through every possible combination of chars in the leftwards direction and
 * prints out the position if a match is found in the list of words to search for.
 */
void searchLeft(int gridColNum, int gridRowNum, char **outGrid, char **unsortedList, int wordListRowSize) {

  for(int r = 0; r < gridRowNum; r++) {
    for(int c = gridColNum - 1; c >= 0; c--) {
      char *word = NULL;
      word = malloc((gridColNum + 1) * sizeof(char));
      int i = 0;
      for(int x = c; x >= 0; x--) {
	word[i] = outGrid[r][x];
	word[i + 1] = '\0';
	i++;
	if(binarySearch(unsortedList, wordListRowSize, word) == true) {
	  printf("%s %d %d L\n", word, r, c);
	}
      }
      free(word);
    }
  } //end left search

} //end searchLeft()

/*
 * Loops through every possible combination of chars in the rightwards direction and
 * prints out the position if a match is found in the list of words to search for.
 */
void searchRight(int gridColNum, int gridRowNum, char **outGrid, char **unsortedList, int wordListRowSize) {

  for(int r = 0; r < gridRowNum; r++) {
    for(int c = 0; c < gridColNum; c++) {
      char *word = NULL;
      word = malloc((gridColNum + 1) * sizeof(char));
      int i = 0;
      for(int x = c; x < gridColNum; x++) {
	word[i] = outGrid[r][x];
	word[i + 1] = '\0';
 	i++;
	if(binarySearch(unsortedList, wordListRowSize, word) == true) {
	  printf("%s %d %d R\n", word, r, c);
	}
      }
      free(word);
    }
  } //end right search

} //end searchRight()

/*
 * Loops through every possible combination of chars in the downwards direction and
 * prints out the position if a match is found in the list of words to search for.
 */
void searchDown(int gridColNum, int gridRowNum, char **outGrid, char **unsortedList, int wordListRowSize) {

  for(int c = 0; c < gridColNum; c++) {
    for(int r = 0; r < gridRowNum; r++) {
      char *word = NULL;
      word = malloc((gridRowNum + 1) * sizeof(char));
      int i = 0;
      for(int x = r; x < gridRowNum; x++) {
	word[i] = outGrid[x][c];
	word[i + 1] = '\0';
	i++;
	if(binarySearch(unsortedList, wordListRowSize, word) == true) {
	  printf("%s %d %d D\n", word, r, c);
	}
      }
      free(word);
    }
  } //end down search

} //end searchDown()

/*
 * Loops through every possible combination of chars in the upwards direction and
 * prints out the position if a match is found in the list of words to search for.
 */
void searchUp(int gridColNum, int gridRowNum, char **outGrid, char **unsortedList, int wordListRowSize) {

  for(int c = 0; c < gridColNum; c++) {
    for(int r = gridRowNum - 1; r >= 0; r--) {
      char *word = NULL;
      word = malloc((gridRowNum + 1) * sizeof(char));
      int i = 0;
      for(int x = r; x >= 0; x--) {
	word[i] = outGrid[x][c];
	word[i + 1] = '\0';
	i++;
	if(binarySearch(unsortedList, wordListRowSize, word) == true) {
	  printf("%s %d %d U\n", word, r, c);
	}
      }
      free(word);
    }
  } //end up search

} //end searchUp()

/*
 * Takes in the dimensions of the list of search words, takes the sorted version of the list,
 * and writes the ist in a file.
 */
void makeList(int wordListRowSize, int wordListColSize, char ***unsortedList, FILE* readUnsortedList) {

  //Fill the 2D array so we can sort the pointers afterwards  
  char a;
  int numRow = 0;
  int numCol = 0;
  int colSize = wordListColSize;

  for(numRow = 0; numRow < wordListRowSize; numRow++) { //used to be numRow < wordListRowSize

    if(numCol >= colSize) { //condition to realloc *unsortedList
      colSize *= 2;
      (*unsortedList)[numRow] = realloc((*unsortedList)[numRow],  (colSize + 1) * sizeof(char));
    } //end if

    while((a = fgetc(readUnsortedList)) != EOF) {

      if(isspace(a)) { //if space, set last char to null and get out of while loop
	(*unsortedList)[numRow][numCol] = '\0';
       	numCol = 0;
	goto here;
      } else {
	if(numCol == 0) { //if this is a new row, allocate a char array for it
	  (*unsortedList)[numRow] = malloc((colSize + 2) * sizeof(char));
	} //end if
	(*unsortedList)[numRow][numCol] = tolower(a);
	numCol++;
      } //end if-else
    
    } //end while
  here:
    continue;
  } //end outer for

} //end makeList
