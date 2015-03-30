/*
 * Homework3, 600.120 Spring 2015
 * wordSearch.h
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

int readGrid(FILE* infile, FILE* outfile, char ***outGrid);

int returnColNum(FILE* infile);

int compare(const void *a, const void *b);

bool binarySearch(char **wordList, int max, char *target);

void searchRight(int gridColNum, int gridRowNum, char **outGrid, char **unsortedList, int wordListRowSize);

void searchLeft(int gridColNum, int gridRowNum, char **outGrid, char **unsortedList, int wordListRowSize);

void searchDown(int gridColNum, int gridRowNum, char **outGrid, char **unsortedList, int wordListRowSize);

void searchUp(int gridColNum, int gridRowNum, char **outGrid, char **unsortedList, int wordListRowSize);

void makeList(int wordListRowSize, int wordListColSize, char ***unsortedList, FILE* readUnsortedList);
