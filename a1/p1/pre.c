#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
   char *line = NULL;
   size_t size;
   while(getline(&line, &size, stdin) != EOF) {
      if (size > 0) printf("%s\n", line);
      else printf("No line.\n");
      printf("%zu\n", size);
   }
   exit(EXIT_SUCCESS);
}
