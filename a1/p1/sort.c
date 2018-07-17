#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ENTRIES = 20;

int get_input(char **buffer);
void print_output(char **buffer);
void sort(char **buffer, int n);

int main(int argc, char *argv[])
{
  char **buffer = (char **)malloc(ENTRIES * sizeof(char *));
  for (int i = 0; i < ENTRIES; i++)
    buffer[i] = NULL;
  int count = get_input(buffer);
  sort(buffer, count);
  print_output(buffer);
  for (int i = 0; i < ENTRIES; i++)
    if (buffer[i])
      free(buffer[i]);
  free(buffer);
  exit(EXIT_SUCCESS);
}

int get_input(char **buffer)
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
    buffer[i] = (char *)malloc(sizeof(char) * (size + 10));
    strncpy(buffer[i++], line, size);
  }
  printf("\n");
  return i;
}

void print_output(char **buffer)
{
  printf("Printing sorted names:\n");
  int i = 0;
  while (buffer[i] != NULL)
    printf("%s\n", buffer[i++]);
  printf("\n");
}

void sort(char **buffer, int n)
{
  char t[500];
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (strcasecmp(buffer[i], buffer[j]) > 0)
      {
        strcpy(t, buffer[j]);
        strcpy(buffer[j], buffer[i]);
        strcpy(buffer[i], t);
      }
  return;
}