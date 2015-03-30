/*
 * Homework3, 600.120 Spring 2015
 * hw3.c
 * Name: Joon Hyuck Choi
 * Date: Feb 27, 2015
 * Assignment 3
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 16:54 02/27/2015
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wordSearch.h"

/*
 * The main driver for the wordSearch program.
 */
int main(int argc, char *argv[]) {

  //Check usage errors
  if(argc == 1) {
    printf("Usage error. Enter the name of the grid text file.\n");
    return 1;
  } //end if

  //Open two files: 1 for reading and another for writing
  FILE* infile1 = fopen(argv[1], "r");
  FILE* outfile = fopen("gridOutput.txt", "w");

  //Check for errors in opening the two files.
  if(infile1 == NULL) {
    printf("Error in opening %s.\n", argv[1]);
    return 1;
  } //end if

  //This output file is for additional testing purposes.
  if(outfile == NULL) {
    printf("Error in opening test output file.\n");
    return 1;
  } //end if

  //Declare a 2D char array
  char **outGrid = NULL;

  //Pass it to function readGrid
  int gridRowNum =  readGrid(infile1, outfile, &outGrid);

  //Check for errors and exit if any are found.
  if(gridRowNum == 0) {
    printf("Empty grid!\n");
    return 1;
  } else if(gridRowNum == -1) {
    printf("The number of columns are different!\n");
    return 1;
  } //end if-elseif
  fclose(infile1); //close infile1

  //Obtain the number of columns in the grid
  FILE* infile2 = fopen(argv[1], "r");
  if(infile2 == NULL) {
    printf("Error in re-opening %s.\n", argv[1]);
    return 1;
  } //end if
  int gridColNum  = returnColNum(infile2);
  fclose(infile2); //close infile2

  //Prompt for words to search for
  printf("Please enter the words you want to search for: ");
  //Take user input and keep looping through
  char *userEntry = NULL;
  
  //Dynamically allocate space for user entry
  int initialEntrySize = 10000;
  userEntry = malloc(initialEntrySize * sizeof(char));
  
  //Open a text file to store the unsorted list of words
  FILE* unsortedListFile = fopen("unsortedListFile.txt", "w");
  int countLine = 0;
  int entryLength = 0;
  int maxEntryLength = 0;

  //Scan the user's input and save it in the list file until EOF is reached
  while(fscanf(stdin, "%s", userEntry) != EOF) {
    fprintf(unsortedListFile, "%s ", userEntry);
    countLine++;
    entryLength = strlen(userEntry);
    if(entryLength > maxEntryLength) {
      maxEntryLength = entryLength;
    }
  } //end while
  fclose(unsortedListFile);

  //Declare a 2D char array to hold the list of words to search for
  char **unsortedList = NULL;
  int wordListRowSize = countLine;
  int wordListColSize = maxEntryLength;
  FILE* readUnsortedList = fopen("unsortedListFile.txt", "r");
  unsortedList = malloc(wordListRowSize * sizeof(char*));

  //Fill the 2D char array with the user's entries
  makeList(wordListRowSize, wordListColSize, &unsortedList, readUnsortedList);

  //Now, sort the **unsortedList
  qsort(unsortedList, countLine, sizeof(char*), compare);

  //Perform searches in all 4 directions.
  searchRight(gridColNum, gridRowNum, outGrid, unsortedList, wordListRowSize);
  searchLeft(gridColNum, gridRowNum, outGrid, unsortedList, wordListRowSize);
  searchDown(gridColNum, gridRowNum, outGrid, unsortedList, wordListRowSize);
  searchUp(gridColNum, gridRowNum, outGrid, unsortedList, wordListRowSize);

  //Free unsortedList's rows
  for(int i = 0; i < wordListRowSize; i++) {
    free(unsortedList[i]);
  } //end for

  //Free outGrid's rows
  for(int i = 0; i < gridRowNum; i++) {
    free(outGrid[i]);
  } //end for

  //Close files
  fclose(outfile); 
  fclose(readUnsortedList);

  //Free everything else that remains to be freed
  free(outGrid);
  free(unsortedList);
  free(userEntry);

  return 0;
} //end main

