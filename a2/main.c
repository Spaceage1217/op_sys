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
  int i, status, procCount;
  // int left_fd[2];
  // int right_fd[2];
  bool redir_out, redir_in;
  char *line;
  char buf[256];
  char infile[256];
  char outfile[256];
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
    infile[0] = '\0';
    outfile[0] = '\0';

    // Get line and process exit conitions
    printf("\nshhh> ");
    if (getline(&line, &size, stdin) == EOF)
      break;
    if (strncasecmp(line, "exit", 4) == 0)
      break;

    // Get piped arguments
    strcpy(buf, line);
    tokenize(buf, args, &procCount);

    findRedirect(args[0], infile, "<");
    if (infile[0] != '\0') redir_in = true;

    findRedirect(args[procCount - 1], outfile, ">");
    if (outfile[0] != '\0') redir_out = true;

    // If pipes exist
    if (procCount > 1) {
      printf("has pipes\n");
      // if (pipe(left_fd) < 0)
      //   exit(EXIT_FAILURE);
      // if (pipe(right_fd) < 0)
      //   exit(EXIT_FAILURE);
    }
    else printf("single process\n");

    for (i = 0; i < procCount; i++)
    {
      // Proc area
      if((pid = fork()) > 0) {
        if (i > 0) {
          // middle children stuff
          // close(left_fd[0]);
          // close(left_fd[1]);
          printf("config pipes for mid proc\n");
        }
        // left_fd[0] = right_fd[0];
        // left_fd[1] = right_fd[1];
        // parent stuff
        printf("configured pipes for process\n");

        // Wait for child to finish before starting again
        if ((waitpid(pid, &status, 0) == pid) && (status != 0))
          perror("Excuted process.\n");
      } else if (pid == 0) {
        
        // Manage files for redirection
        if (i == 0 && redir_in) {
          printf("Input: %s\n", infile);
        }
        if (i == procCount - 1 && redir_out) {
          printf("Output: %s\n", outfile);
        }
    
        char *const argv[2] = { args[i], NULL };
        execvp(argv[0], argv);
        // Shouldn't get here
        fprintf(stderr, "Process { %s } didn't exec.\n", args[i]);
      } else perror("Something broke");
    }
  }
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