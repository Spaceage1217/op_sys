Assignment 1

How to run:
1. With GNU Make
  a. You can build and run all the programs by running "make" in the a1 directory
  b. For your convenience, you can run "make test" in the a1 directory. This will build,
  run, and then remove the object and executable files from your computer.
  c. You can run each problem individually. A Makefile has been provided in a1: problem1-3.
  d. Run "make" or "make test" inside each problem directory you want to test.
  To remove files: You can run "make clean" in any directory to remove the executable and object files from 
  that directory.
2. Manually
  a. Problem 1
    Build: 
      gcc -Wall -Werror -g pre.o -o pre.c
      gcc -o pre pre.o
      gcc -Wall -Werror -g sort.o -o sort.c
      gcc -o sort sort.o
    Execute:
      ./pre
      ./sort
  b. Problem 2
    Build: 
      gcc -Wall -Werror -g problem2.o -o problem2.c
      gcc -o problem2 problem2.o
    Execute:
      ./problem1
  c. Problem 3
    Build: 
      gcc -Wall -Werror -g problem3.o -o problem3.c
      gcc -o problem3 problem3.o
    Execute:
      ./problem3
