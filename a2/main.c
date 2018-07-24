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

void tokenize(char *line, char **args, int *procCount);
void findRedirect(char *arg, char *reFile, char *delim);
void findOutput(char *arg, char *outFile);
void trim(char *str);

int main()
{
  int i;
  int procCount;
  // int left_fd[2];
  // int right_fd[2];
  bool redir_out, redir_in;
  char *line;
  char buf[256];
  char **args = (char **)malloc(MAX_ARGS * sizeof(char *));
  for (i = 0; i < MAX_ARGS; i++)
    args[i] = NULL;

  size_t size;
  pid_t pid;

  while (1)
  {
    // Init
    redir_in = redir_out = false;
    procCount = 0;

    // Get line and process exit conitions
    printf("\nshhh> ");
    if (getline(&line, &size, stdin) == EOF)
      break;
    if (strncasecmp(line, "exit", 4) == 0)
      break;

    // Get piped arguments
    strcpy(buf, line);
    tokenize(buf, args, &procCount);

    char infile[256];
    findRedirect(args[0], infile, "<");
    if (infile != NULL) redir_in = true;

    char outfile[256];
    findRedirect(args[procCount - 1], outfile, ">");
    if (outfile != NULL) redir_out = true;

    for (i = 0; i < procCount; i++)
    {
      if (procCount > 1) {
        printf("has pipes\n");
        // pipe(left_fd);
        // pipe(right_fd);
      }
      else printf("single process\n");

      // Proc area
      if((pid = fork()) > 0) {
        if (i > 0) {
          // middle children stuff
          // close(left_fd[0]);
          // close(left_fd[1]);
          printf("closing left pipes for middle processes\n");
        }
        // left_fd[0] = right_fd[0];
        // left_fd[1] = right_fd[1];
        // parent stuff
        printf("executing parent arg\n", args[i]);
        wait(NULL);
        printf("next process\n");
      } else if (pid == 0) {
        printf("child stuff\n");
        // Manage files for redirection
        if (i == 0 && infile && redir_in) printf("Input: %s\n", infile);
        if (i == procCount - 1 && outfile && redir_out) printf("Output: %s\n", outfile);
        exit(EXIT_SUCCESS);
      } else perror("Something broke");
    }
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
    if (args[i])
      free(args[i]);
  free(args);
  exit(EXIT_SUCCESS);
}

void tokenize(char *line, char **args, int *procCount)
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

  *procCount = i;
  // Ignore stale args
  args[i] = NULL;
}

void findRedirect(char *arg, char *reFile, char *delim)
{
  //printf("Testing: %s\n", arg);
  char *match = strtok(arg, delim);
  if (match != NULL)
  {
    trim(match);
    // printf("arg: %s\n", match);
    strcpy(arg, match);
  } else return;
  
  match = strtok(NULL, " ");
  if (match != NULL) {
    trim(match);
    // printf("infile: %s\n", match);
    strcpy(reFile, match);
  }
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