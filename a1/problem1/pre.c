/*
  Assignment 1: Problem 1
  pre.c
  Developer: Michael Scales
  Operating Systems
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ENTRIES = 100;

/*
  getInput:
    Fill an empty buffer with an array of character arrays.
    Use the input from stdin to get a name, an the number of courses
    for the user. If course >= 5, then we add the name to the buffer.
*/
void getInput(char **buffer);

/*
  printInput:
    Print all the names in the buffer.
*/
void printInput(char **buffer);


int main(int argc, char *argv[])
{
  // Get memory for the array of char arrays
  char **buffer = (char **)malloc(ENTRIES * sizeof(char *));
  for (int i = 0; i < ENTRIES; i++)
    buffer[i] = NULL;

  // Get input, prune names with courses <5, and print
  getInput(buffer);
  printInput(buffer);

  // Free memory
  for (int i = 0; i < ENTRIES; i++)
    if (buffer[i])
      free(buffer[i]);
  free(buffer);

  exit(EXIT_SUCCESS);
}

void getInput(char **buffer)
{
  int i = 0;
  size_t size;
  char *line;
  while (1)
  {
    int examCount;
    printf("Enter a name (Ctrl-D to terminate the input):\t");
    // Quit if we're done or before we run off the array
    if (i >= ENTRIES)
    {
      printf("All entries filled. Exiting from input.");
      break;
    }
    if (getline(&line, &size, stdin) == EOF)
      break;

    printf("Enter the number of courses:\t");
    scanf("%d", &examCount);
    while (fgetc(stdin) != '\n')
      ; // Read until a newline is found

    if (examCount > 12)
    {
      printf("Max number of courses is 12. Please try again.\n");
      continue;
    }

    if (examCount > 4)
    {
      // Trim newline from getline
      line[strcspn(line, "\n")] = 0;

      // Allocate and copy the line to the buffer
      buffer[i] = (char *)malloc(sizeof(char) * (size + 10));
      strncpy(buffer[i++], line, size);
    }
  }
  printf("\n");
}

void printInput(char **buffer)
{
  printf("Printing students with 5 or more courses:\n");
  int i = 0;
  while (buffer[i] != NULL)
    printf("%s\n", buffer[i++]);
  printf("\n");
}