#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ENTRIES = 12;

void get_input(char **buffer);
void print_output(char **buffer);

int main(int argc, char *argv[])
{
  char **buffer = (char **)malloc(ENTRIES * sizeof(char *));
  for (int i = 0; i < ENTRIES; i++)
    buffer[i] = NULL;
  get_input(buffer);
  print_output(buffer);
  for (int i = 0; i < ENTRIES; i++)
    if (buffer[i])
      free(buffer[i]);
  free(buffer);
  exit(EXIT_SUCCESS);
}

void get_input(char **buffer)
{
  int i = 0;
  size_t size;
  char *line;
  while (1)
  {
    int examCount;
    printf("Enter a name (Ctrl-D to terminate the input):\t");
    // Quit if we're done or before we run off the array
    if (getline(&line, &size, stdin) == EOF || i >= ENTRIES)
      break;

    printf("Enter the number of courses:\t");
    scanf("%d", &examCount);
    while (fgetc(stdin) != '\n')
      ; // Read until a newline is found

    if (examCount > 4)
    {
      // Trim newline
      line[strcspn(line, "\n")] = 0;
      buffer[i] = (char *)malloc(sizeof(char) * (size + 10));
      strncpy(buffer[i++], line, size);
    }
  }
  printf("\n");
}

void print_output(char **buffer)
{
  printf("Printing students with 5 or more courses:\n");
  int i = 0;
  while (buffer[i] != NULL)
    printf("%s\n", buffer[i++]);
  printf("\n");
}