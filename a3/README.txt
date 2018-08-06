Assignment 3

How to run:
1. With GNU Make
  a. You can build and run all the programs by running "make" in the a3 directory
  b. For your convenience, you can run "make test" in the a3 directory. This will build,
  run, and then remove the object and executable files from your computer.
  To remove files: You can run "make clean" in any directory to remove the executable and object files from 
  that directory.
2. Manually
  a. Lab 2
    Build: 
      gcc -Wall -Werror -g threadPartA.o -o threadPartA.c
      gcc -o threadPartA threadPartA.o
      gcc -Wall -Werror -g threadPartB.o -o threadPartB.c
      gcc -o threadPartB threadPartB.o
    Execute:
      ./threadPartA
      ./threadPartB
