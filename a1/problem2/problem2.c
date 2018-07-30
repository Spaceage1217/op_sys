/*
  Assignment 1: Problem 1
  problem2.c
  Developer: Michael Scales
  Operating Systems
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  pid_t pid;
  int preStatus;
  int fd[2];
  if (pipe(fd) < 0)
    return 1;
  if ((pid = fork()) == 0)
  { // execute pre
    printf(
        "Enter a name (press enter), then enter the number of courses."
        "(press enter) \n"
        "Repeat until completed. (Ctrl-D to terminate the input)\n");
    dup2(fd[1], 1);
    close(fd[0]);
    close(fd[1]);
    // printf("Executing pre process.\n");
    char *argv[] = {"./pre", NULL};
    execvp(argv[0], argv);
  }

  if (pid < 0)
  {
    fprintf(stderr, "Pre process failed to fork.");
    exit(EXIT_FAILURE);
  }

  // Prevent race condition between pre and sort
  if ((waitpid(pid, &preStatus, 0) == pid) && (preStatus != 0))
    perror("Pre process.\n");
  else
    printf(
        "Pre process completed: %s\n", !WEXITSTATUS(preStatus) ? "OK!" : "FAILED.");

  if (pid > 0)
  { // execute sort
    close(0);
    dup(fd[0]);
    close(fd[0]);
    close(fd[1]);
    /*size_t size;
    char *line;
    while (getline(&line, &size, stdin) != EOF)
      printf("%s", line);*/
    /*dup2(fd[0], 0);
      close(fd[0]);
      close(fd[1]);*/
    char* argv[] = { "./sort", NULL };
    execvp(argv[0], argv);
  }
  close(fd[0]);
  close(fd[1]);

  // Exit from the parent process
  exit(EXIT_SUCCESS);
}
