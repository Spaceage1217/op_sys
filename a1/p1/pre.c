#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
   int entries = 5;
   char *line = NULL;
   size_t size;
   char** buffer = (char**)malloc(entries * sizeof(char*));
   for (int i = 0; i < entries; i++) buffer[i] = NULL;
   while (getline(&line, &size, stdin) != EOF) {
      line[strcspn(line, "\n")] = 0;
      printf("%s\n", line);
      /*if (size > 0) printf("%s\n", line);
      else printf("No line.\n");
      printf("%zu\n", size);*/
   }
   for (int i = 0; i < entries; i++) if (buffer[i]) free(buffer[i]);
   free(buffer);
   exit(EXIT_SUCCESS);
}
