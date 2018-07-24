/*			Lab 2 Partial Example			*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int main()
{
  //char *path, *argv[20], buf[80], n, *p;
  //int status;
  size_t size;
  char *line;
  //bool m, inword, continu;

  while (1)
  {
    char s[256];
    printf("\nshhh> ");
    if (getline(&line, &size, stdin) == EOF) break;
    strcpy(s, line);
    char* token = strtok(s, " ");
    printf("Got words:");
    while (token) {
        printf("token: %s\n", token);
        token = strtok(NULL, " ");
    }
    break;
    //printf("Parsing string: %s %s\n", argv[0], argv[1]);
  }
  // while (1)
  // {
  //   inword = false;
  //   p = buf;
  //   m = false;
  //   continu = false;

  //   printf("\nshhh> ");

  //   while ((n = getchar()) != '\n' || continu)
  //   {
  //     if (n == ' ')
  //     {
  //       if (inword)
  //       {
  //         inword = false;
  //         *p++ = 0;
  //       }
  //     }

  //     else if (n == '\n')
  //       continu = false;

  //     else if (n == '\\' && !inword)
  //       continu = true;

  //     else
  //     {
  //       if (!inword)
  //       {
  //         inword = true;
  //         argv[m++] = p;
  //         *p++ = n;
  //       }
  //       else
  //         *p++ = n;
  //     }
  //   }

  //   *p++ = 0;
  //   argv[m] = 0;
  //   printf("Parsing string: %s %s\n", argv[0], argv[1]);

  //   if (strcmp(argv[0], "quit") == 0)
  //     exit(EXIT_SUCCESS);

  //   if (fork() == 0)
  //   {
  //     execvp(argv[0], argv);
  //     printf(" didn't exec \n ");
  //   }
  //   wait(&status);
  // }
  exit(EXIT_SUCCESS);
}