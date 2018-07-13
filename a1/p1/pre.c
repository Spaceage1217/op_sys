#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
   int entries = 500;
   char *line = NULL;
   size_t size;
   char** buffer = (char**)malloc(entries * sizeof(char*));
   while(getline(&line, &size, stdin) != EOF) {
      //buffer[strcspn(buffer, "\n")] = 0;
      //printf("%s\n", buffer);
      /*if (size > 0) printf("%s\n", line);
      else printf("No line.\n");
      printf("%zu\n", size);*/
   }
   free(buffer);
   exit(EXIT_SUCCESS);
}
