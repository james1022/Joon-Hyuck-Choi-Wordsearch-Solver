#600.120 HW3
#Name: Joon Hyuck Choi
#email: jchoi100@jhu.edu
#BB: jchoi100
#Phone: 667-239-0288
#Date: 02/27/2015
#
#
# Makefile for hw3
#
# How to use:
#
#   compile: make
#
#   compile test file and run: make test
#
#   compile hw3 and run: make wordSearch.o
#                        make hw3.o
#                        make hw3
#         (on Makefile)  make hw3run (this will put a file named "grid.txt" as
#                                     default input. If the user wants his/her
#				      own file, must run hw3 on command line)
#		*To run hw3 on command line, just enter ./hw3 <"inputfile.txt">
#
#   remove compilation, tildy, and executable files: make clean
#

# Long flags in one line
CFLAGS = -std=c99 -Wall -Wextra -pedantic -O
#CFLAGS = -std=c99 -Wall -Wextra -pedantic -O0 -g
# this CFLAG above to run with debugging flag "-g"

bin: hw3

test: testWordSearch
	echo "Test in progress..."
	./testWordSearch
	echo "All tests over."

testWordSearch: testWordSearch.c
	gcc $(CFLAGS) -o testWordSearch testWordSearch.c

wordSearch.o: wordSearch.c wordSearch.h
	gcc $(CFLAGS) -c wordSearch.c

hw3.o: hw3.c wordSearch.h
	gcc $(CFLAGS) -c hw3.c 

hw3: hw3.o wordSearch.o
	gcc $(CFLAGS) -o hw3 hw3.o wordSearch.o

hw3run: hw3.c wordSearch.h
	./hw3 grid.txt

clean:
	rm -f *.o hw3 testWordSearch *~
