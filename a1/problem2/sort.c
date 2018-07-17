/*
  Assignment 1: Problem 2
  sort.c
  Developer: Michael Scales
  Operating Systems
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int ENTRIES = 20;

/*
  getInput:
    Fill an empty buffer with an array of character arrays.
    Use the stdin to get a name and add to the buffer.
    Returns: an integer count of the items in the buffer.
*/
int getInput(char **buffer);

/*
  printInput:
    Print all the names in the buffer.
*/
void printInput(char **buffer);

/*
  sort:
    Sort n items in the buffer. Sorts in ascending order.
    For a matching letter with a differing case, the lowercase is
    displayed first.
*/
void sort(char **buffer, int n);

/*
  swap:
    Swap the position of the two character strings.
*/
void swap(char **a, char **b);


int main(int argc, char *argv[])
{
  // Get memory for the array of char arrays
  char **buffer = (char **)malloc(ENTRIES * sizeof(char *));
  for (int i = 0; i < ENTRIES; i++)
    buffer[i] = NULL;

  // Get input, sort, and then print
  int count = getInput(buffer);
  sort(buffer, count);
  printInput(buffer);

  // Free memory
  for (int i = 0; i < ENTRIES; i++)
    if (buffer[i])
      free(buffer[i]);
  free(buffer);

  // exit(EXIT_SUCCESS);
  return 0;
}

int getInput(char **buffer)
{
  int i = 0;
  size_t size;
  char *line;
  while (1)
  {
    printf("Enter a name (Ctrl-D to terminate the input):\t");
    if (getline(&line, &size, stdin) == EOF || i >= ENTRIES)
      break;

    // Trim newline
    line[strcspn(line, "\n")] = 0;

    // Allocate and copy the line to the buffer
    buffer[i] = (char *)malloc(sizeof(char) * (size + 10));
    strncpy(buffer[i++], line, size);
  }
  printf("\n");
  return i;
}

void printInput(char **buffer)
{
  printf("Printing sorted names:\n");
  int i = 0;
  while (buffer[i] != NULL)
    printf("%s\n", buffer[i++]);
  printf("\n");
}

void sort(char **buffer, int n)
{
  int cmpVal;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
    {
      cmpVal = strcasecmp(buffer[i], buffer[j]);
      // > 0 indicates the string i is higher ascending than j
      if (cmpVal > 0)
        swap(&buffer[i], &buffer[j]);
      // == 0 indicates the strings are equal w/o checking 
      // case-sensitivity
      else if (cmpVal == 0)
        // Only swap if the the char string is upper
        if (isupper(buffer[i][0]))
          swap(&buffer[i], &buffer[j]);
    }
}

void swap(char **a, char **b)
{
  char *temp = *a;
  *a = *b;
  *b = temp;
}