/*			Lab 2 Partial Example			*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

static int MAX_ARGS = 50;

void tokenize(char *line, char **args, int *pipeCnt);
void findInput(char *arg, char *inFile);
void findOutput(char *arg, char *outFile);
void trim(char *str);

int main()
{
  size_t size;
  int i;
  char *line;
  char buf[256];
  bool redir_out, redir_in;
  char **args = (char **)malloc(MAX_ARGS * sizeof(char *));
  int pipeCnt;
  for (i = 0; i < MAX_ARGS; i++)
    args[i] = NULL;

  while (1)
  {
    // Init
    redir_in = redir_out = false;
    pipeCnt = 0;

    // Get line and process exit conitions
    printf("\nshhh> ");
    if (getline(&line, &size, stdin) == EOF)
      break;
    if (strncasecmp(line, "exit", 4) == 0)
      break;

    // Get piped arguments
    strcpy(buf, line);
    tokenize(buf, args, &pipeCnt);

    for (i = 0; i < pipeCnt; i++)
    {
      printf("%s\n", args[i]);
    }
    // while (token) {
    //     printf("token: %s\n", token);
    //     token = strtok(NULL, " ");
    // }
    // printf("words");
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
  for (i = 0; i < MAX_ARGS; i++)
  {
    if (args[i])
    {
      //printf("%s\n", args[i]);
      free(args[i]);
    }
  }
  free(args);
  exit(EXIT_SUCCESS);
}

void tokenize(char *line, char **args, int *pipeCnt)
{
  int i = 0,
      size;
  char *cmd = strtok(line, "|");

  while (cmd != NULL && i < MAX_ARGS)
  {
    trim(cmd);
    size = strlen(cmd);
    args[i] = (char *)malloc(size * sizeof(char));
    strncpy(args[i++], cmd, size);
    cmd = strtok(NULL, "|");
  }

  *pipeCnt = i;
  // Ignore stale args
  args[i] = NULL;
}

void findInput(char *arg, char *inFile)
{
  // char *match;
  // int len = strlen(inFile);
  // while ((match = strstr(string, sub))) {
  //     *match = '\0';
  //     strcat(string, match+len);
  // }
}

void trim(char *str)
{
  if (!str)
    return;

  char *ptr = str;
  int len = strlen(ptr);

  while (len - 1 > 0 && isspace(ptr[len - 1]))
    ptr[--len] = 0;

  while (*ptr && isspace(*ptr))
    ++ptr, --len;

  memmove(str, ptr, len + 1);
}