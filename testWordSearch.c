/*
 * Homework3, 600.120 Spring 2015
 * testWordSearch.c
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
#include <assert.h>

/*
 * Adapted from sample code from hw2.
 */
bool fileeq(char lhsName[], char rhsName[]) {
    FILE* lhs = fopen(lhsName, "r");
    FILE* rhs = fopen(rhsName, "r");

    // don't compare if we can't open the files
    if (!lhs || !rhs) return false;

    bool match = true;
    // read until both of the files are done or there is a mismatch
    while (!feof(lhs) || !feof(rhs)) {
        if (feof(lhs) ||                  // lhs done first
            feof(rhs) ||                  // rhs done first
            (fgetc(lhs) != fgetc(rhs))) { // chars don't match
            match = false;
            break;
        }
    }
    fclose(lhs);
    fclose(rhs);
    return match;
} //end fileeq()

/*
 * Adapted from sample code from hw2.
 */
void test_fileeq() {
    FILE* fptr = fopen("test1.txt", "w");
    fprintf(fptr, "this\nis\na test\n");
    fclose(fptr);

    fptr = fopen("test2.txt", "w");
    fprintf(fptr, "this\nis\na different test\n");
    fclose(fptr);

    fptr = fopen("test3.txt", "w");
    fprintf(fptr, "this\nis\na test\n");
    fclose(fptr);

    assert(fileeq("test1.txt", "test1.txt"));
    assert(fileeq("test2.txt", "test2.txt"));
    assert(!fileeq("test2.txt", "test1.txt"));
    assert(!fileeq("test1.txt", "test2.txt"));
    assert(fileeq("test3.txt", "test3.txt"));
    assert(fileeq("test1.txt", "test3.txt"));
    assert(fileeq("test3.txt", "test1.txt"));
    assert(!fileeq("test2.txt", "test3.txt"));
    assert(!fileeq("test3.txt", "test2.txt"));
    assert(!fileeq("", ""));  // can't open file
} //end test_fileeq()

/*
 * Reads and saves the grid that the user input from the command line.
 * Returns the number of lines read from the grid file.
 * Copied from wordSearch.c, and modified just some variables to suit this tester.
 */
int readGrid(FILE* infile, FILE** outfile, char ***outGrid) {

  int ch; //the character that'll be read in from the infile
  int prevNumCol = 0; //numCol from the previous row
  int numRow = 0;
  int numCol = 0;
  int initialRowSize = 10;
  int initialColSize = 10;

  (*outGrid) = malloc(initialRowSize * sizeof(char*)); //alloc 10 rows of space for **outGrid

  while((ch = fgetc(infile)) != EOF) { //while the EOF has not been reached

    if(numRow >= initialRowSize) { //condition to realloc **outGrid
      initialRowSize *= 2; //double the size
      (*outGrid) = realloc((*outGrid), initialRowSize * sizeof(char*)); //realloc original
    } //end if

    if(numCol >= initialColSize) { //condition to realloc *outGrid
      initialColSize *= 2; //double the size
      (*outGrid)[numRow] = realloc((*outGrid)[numRow], (initialColSize + 1) * sizeof(char));
    } //end if
 
    if(isspace(ch)) { //if next character is a nextline,
      if(ch == '\n') {
	if(numRow != 0 && numCol == 0) {
       	  break;
	} else if(numRow != 0 && numCol != prevNumCol) { //if numRow != 0, compare the current numCol with previous.
	  return 0; //return -1 to indicate error
	} //end if
	if(numRow == 0 && numCol == 0) { //if we have a new line at the first row
	  return -1;
	}
	fprintf(*outfile, "%c", ch);
	prevNumCol = numCol; //save current number of columns to compare
	numCol = 0; //set number of columns back to 0
	numRow++; //increment the number of rows
      } else {
	goto here;
      }
    } else { //if ch is just a char save the char in outGrid
      if(numCol == 0) { //if this is a new row
	(*outGrid)[numRow] = malloc((initialColSize + 1) * sizeof(char));
      }
      (*outGrid)[numRow][numCol] = tolower(ch);
	  fprintf(*outfile, "%c", ch);
      numCol++; //increment the number of columns
       
   } //end if-elseif-else

  here:
    continue;
  } //end while

  return numRow; //return the number of rows(lines) in the grid text file

} //end readGrid()

/*
 * Tests the readGrid() function above.
 */
void testReadGrid() {

  FILE* infile1 = fopen("readGridTest.txt", "w");
  char inputGrid[4][5] = {"abcde", "fghij", "klmno", "pqrst"};
  for(int r = 0; r < 4; r++) {
	  for(int c = 0; c < 5; c++) {
		  fprintf(infile1, "%c", inputGrid[r][c]);
	  }
	  fprintf(infile1, "\n");
  }
  //Declare a 2D char array
  char **outGrid = NULL;
  FILE* outfile = fopen("readGridTestCompare.txt", "w");
  //Pass it to function readGrid
  int a = readGrid(infile1, &outfile, &outGrid);

  fclose(infile1);
  fclose(outfile);
  assert(a != -1);

  for(int i = 0; i < 4; i++) {
    free(outGrid[i]);
  }
  free(outGrid);

  //Second test
  char **outGrid2 = NULL;
  FILE* infile2 = fopen("readGridTest2.txt", "w");
  FILE* outfile2 = fopen("readGridTestCompare2.txt", "w");
  char inputGrid2[4][5] = {"", "", "", ""};
  for(int r = 0; r < 4; r++) {
	  for(int c = 0; c < 5; c++) {
		  fprintf(infile2, "%c", inputGrid2[r][c]);
	  }
	  fprintf(infile2, "\n");
  }
  int b = readGrid(infile2, &outfile2, &outGrid2);
  fclose(infile2);
  fclose(outfile2);
  assert(b == 0);

  for(int i = 0; i < 4; i++) {
    free(outGrid2[i]);
  }
  free(outGrid2);


} //end testReadGrid()

/*
 * Returns the number of columns in a grid text file.
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

int compare(const void *a, const void *b) {
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
} //end compare()

/*
 * binarySearch method specifically for a wordList of a specified size.
 */
bool binarySearch(char wordList[1][5], int max, char *target) {
  int position = 0;
  int begin = 0;
  int end = max - 1;
  int cond = 0;

  while(begin <= end) {
    position = (begin + end) / 2;
    cond = strcmp(wordList[position], target);
    if(cond == 0) {
      return true;
    } else if (cond < 0) {
      begin = position + 1;
    } else {
      end = position - 1;
    }
  }
  return false;

} //end binarySearch()

/*
 * binarySearch for a bigger grid. The specification of the input
 * word list does not affect the functionality of this function.
 */
bool binarySearch2(char wordList[3][5], int max, char *target) {

  int position = 0;
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
  }
  return false;

} //end binarySearch2()

/*
 * Tests the binarySearch() function above.
 */
void testBinarySearch() {

  char wordList[3][5] = {"cake", "fish", "duck"};
  assert(binarySearch2(wordList, 3, "cake"));
  assert(binarySearch2(wordList, 3, "fish"));
  assert(!binarySearch2(wordList, 3, "tool"));
  assert(!binarySearch2(wordList, 3, "game"));

} //end testBinarySearch()

void searchLeft(int gridColNum, int gridRowNum, char outGrid[5][4], char unsortedList[1][5], int wordListRowSize) {

  FILE* testLeftFile = fopen("testLeftFile.txt", "w");
  bool find = false;
  for(int r = 0; r < gridRowNum; r++) {
    for(int c = gridColNum - 1; c >= 0; c--) {
      char *word = NULL;
      word = malloc((gridColNum  + 1) * sizeof(char));
      int i = 0;
      for(int x = c; x >= 0; x--) {
	word[i] = outGrid[r][x];
	word[i + 1] = '\0';
	i++;
	find = binarySearch(unsortedList, wordListRowSize, word);
	if(find == true) {
	  fprintf(testLeftFile, "%s %d %d L\n", word, r, c);
	}
      }
      free(word);
    }
  } //end left search
  fclose(testLeftFile);
} //end searchLeft()

void testSearchLeft() {

  int gridColNum = 4;
  int gridRowNum = 5;

  char outGrid[5][4] = {"zzzz", 
			"hsif", 
			"zzzz", 
			"llew", 
			"zzzz"};

  int wordListRowSize = 2;

  char list1[1][5] = {"fish"};
  searchLeft(gridColNum, gridRowNum, outGrid, list1, wordListRowSize);
  
  char expectedOutput1[1][12] = {"fish 1 3 L",
								 };
  //store the expected output in a .txt file
  FILE* compareLeftFile1 = fopen("compareLeft1.txt", "w");

  fprintf(compareLeftFile1, "%s\n", expectedOutput1[0]);

  //close file
  fclose(compareLeftFile1);
  assert(fileeq("compareLeft1.txt", "testLeftFile.txt"));

  //Second test
  char list2[1][5] = {"well"};

  searchLeft(gridColNum, gridRowNum, outGrid, list2, wordListRowSize);

  char expectedOutput2[1][12] = {"well 3 3 L",
								 };

  //store the expected output in a .txt file
  FILE* compareLeftFile2 = fopen("compareLeft2.txt", "w");

  fprintf(compareLeftFile2, "%s\n", expectedOutput2[0]);

  //close file
  fclose(compareLeftFile2);

  //assert the two files contain the same contents
  assert(fileeq("compareLeft2.txt", "testLeftFile.txt"));

} //end testSearchLeft()

void searchRight(int gridColNum, int gridRowNum, char outGrid[5][4], char unsortedList[1][5], int wordListRowSize) {
  
  FILE* testRightFile = fopen("testRightFile.txt", "w");
  for(int r = 0; r < gridRowNum; r++) {
    for(int c = 0; c < gridColNum; c++) {
      char *word = NULL;
      word = malloc((gridColNum + 1) * sizeof(char));
      int i = 0;
      for(int x = c; x <= gridColNum; x++) {
	word[i] = outGrid[r][x];
	word[i + 1] = '\0';
	i++;
	if(binarySearch(unsortedList, wordListRowSize, word) == true) {
	  fprintf(testRightFile, "%s %d %d R\n", word, r, c);
	}
      }
      free(word);
    }
  } //end right search
  fclose(testRightFile);
} //end searchRight()

void testSearchRight() {
  
  int gridColNum = 4;
  int gridRowNum = 5;
  
  char outGrid[5][4] = {"zzzz", 
			"cate", 
			"zzzz", 
			"cake", 
			"zzzz"};
	
  int wordListRowSize = 2;

  char list1[1][5] = {"cate"};

  searchRight(gridColNum, gridRowNum, outGrid, list1, wordListRowSize);

  char expectedOutput1[1][12] = {"cate 1 0 R"};

  //store the expected output in a .txt file
  FILE* compareRightFile1 = fopen("compareRight1.txt", "w");

  fprintf(compareRightFile1, "%s\n", expectedOutput1[0]);

  //close file
  fclose(compareRightFile1);
  assert(fileeq("compareRight1.txt", "testRightFile.txt"));

  //Second test
  char list2[1][5] = {"cake"};

  searchRight(gridColNum, gridRowNum, outGrid, list2, wordListRowSize);

  char expectedOutput2[1][12] = {"cake 3 0 R"};

  //store the expected output in a .txt file
  FILE* compareRightFile2 = fopen("compareRight2.txt", "w");

  fprintf(compareRightFile2, "%s\n", expectedOutput2[0]);

  //close file
  fclose(compareRightFile2);

  //assert the two files contain the same contents
  assert(fileeq("compareRight2.txt", "testRightFile.txt"));

} //end testSearchRight()

void searchDown(int gridColNum, int gridRowNum, char outGrid[5][4], char unsortedList[1][5], int wordListRowSize) {

  FILE* testDownFile = fopen("testDownFile.txt", "w");
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
	  fprintf(testDownFile, "%s %d %d D\n", word, r, c);
	}
      }
      free(word);
    }
  } //end down search
  fclose(testDownFile);
} //end searchDown()

void testSearchDown() {

  int gridColNum = 4;
  int gridRowNum = 5;

  char outGrid[5][4] = {"mzzz", 
			"azzf", 
			"kzzi", 
			"ezzs", 
			"zzzh"};

  int wordListRowSize = 2;

  char list1[1][5] = {"make"};

  searchDown(gridColNum, gridRowNum, outGrid, list1, wordListRowSize);

  char expectedOutput1[1][12] = {"make 0 0 D",
  };

  //store the expected output in a .txt file
  FILE* compareDownFile1 = fopen("compareDown1.txt", "w");

  fprintf(compareDownFile1, "%s\n", expectedOutput1[0]);

  //close file
  fclose(compareDownFile1);
  assert(fileeq("compareDown1.txt", "testDownFile.txt"));

  //Second test
  char list2[1][5] = {"fish"};

  searchDown(gridColNum, gridRowNum, outGrid, list2, wordListRowSize);

  char expectedOutput2[1][12] = {"fish 1 3 D" };

  //store the expected output in a .txt file
  FILE* compareDownFile2 = fopen("compareDown2.txt", "w");

  fprintf(compareDownFile2, "%s\n", expectedOutput2[0]);

  //close file
  fclose(compareDownFile2);

  //assert the two files contain the same contents
  assert(fileeq("compareDown2.txt", "testDownFile.txt"));

} //end testSearchDown()

void searchUp(int gridColNum, int gridRowNum, char outGrid[5][4], char unsortedList[1][5], int wordListRowSize) {
	
  FILE* testUpFile = fopen("testUpFile.txt", "w");
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
	  fprintf(testUpFile, "%s %d %d U\n", word, r, c);
	}
      }
      free(word);
    }
  } //end up search
  fclose(testUpFile);
} //end searchUp()

void testSearchUp() {

  int gridColNum = 4;
  int gridRowNum = 5;

  char outGrid[5][4] = {"tzzz", 
			"szde", 
			"ezff", 
			"tzda", 
			"zzss"};

  int wordListRowSize = 2;

  char list1[1][5] = {"test"};

  searchUp(gridColNum, gridRowNum, outGrid, list1, wordListRowSize);

  char expectedOutput1[1][12] = {"test 3 0 U"};

  //store the expected output in a .txt file
  FILE* compareUpFile1 = fopen("compareUp1.txt", "w");

  fprintf(compareUpFile1, "%s\n", expectedOutput1[0]);

  //close file
  fclose(compareUpFile1);
  assert(fileeq("compareUp1.txt", "testUpFile.txt"));

  //Second test
  char list2[1][5] = {"safe"};

  searchUp(gridColNum, gridRowNum, outGrid, list2, wordListRowSize);

  char expectedOutput2[1][12] = {"safe 4 3 U"};

  //store the expected output in a .txt file
  FILE* compareUpFile2 = fopen("compareUp2.txt", "w");

  fprintf(compareUpFile2, "%s\n", expectedOutput2[0]);

  //close file
  fclose(compareUpFile2);

  //assert the two files contain the same contents
  assert(fileeq("compareUp2.txt", "testUpFile.txt"));

} //end testSearchUp()


void makeList(int wordListRowSize, int wordListColSize, char ***unsortedList, FILE* readUnsortedList) {

  //Fill the 2D array so we can sort the pointers afterwards  
  char a;
  int numRow = 0;
  int numCol = 0;

  for(numRow = 0; numRow < wordListRowSize; numRow++) {

    if(numCol >= wordListColSize) { //condition to realloc *unsortedList
      wordListColSize *= 2;
      (*unsortedList)[numRow] = realloc((*unsortedList)[numRow],  (wordListColSize + 1) * sizeof(char));
    } //end if

    while((a = fgetc(readUnsortedList)) != EOF) {

      if(isspace(a)) { //if space, set last char to null and get out of while loop
	(*unsortedList)[numRow][numCol] = '\0';
       	numCol = 0;
	goto here;
      } else {
	if(numCol == 0) { //if this is a new row, allocate a char array for it
	  (*unsortedList)[numRow] = malloc((wordListColSize + 1) * sizeof(char));
	} //end if
	(*unsortedList)[numRow][numCol] = tolower(a);
	numCol++;
      } //end if-else
    
    } //end while
  here:
    continue;
  } //end outer for

} //end makeList()

int main(void) {

  printf("\nTesting fileeq...\n");

        test_fileeq();

  printf("Passed fileeq tests.\n\n");

  printf("Running readGrid test...\n");
	
	testReadGrid();
	
  printf("Passed readGrid test.\n\n");

  printf("Running binarySearch test...\n");

        testBinarySearch();

  printf("Passed binarySearch tests.\n\n");

  printf("Running wordsearch tests...\n");
 
        testSearchUp();
	testSearchDown();
	testSearchRight();
	testSearchLeft();

  printf("Passed wordsearch tests.\n\n");

  return 0;
} //end main
