/*
  Assignment 1: Problem 3
  problem3.c
  Developer: Michael Scales
  Operating Systems
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
  processRunner:
    Takes a command and the argv arguments minus the parent's executable.
    Runs the command in execvp and have the parent wait for the process
    to complete.
    Returns a non-zero for a failed execution.
*/
int processRunner(char *command, char **arguments);

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "%s takes at least one argument.", argv[0]);
    exit(1);
  }

  // Shift arguments -> remove the parent's executable
  int i;
  for (i = 1; i < argc; i++)
    argv[i - 1] = argv[i];

  int status = processRunner(argv[0], argv);
  printf(
    "Command execution %s.\n",
    (status == 0) ? "completed successfully" : "failed"
  );

  // Exit from the parent process
  exit(EXIT_SUCCESS);
}

int processRunner(char *command, char **arguments)
{
  if (command == NULL || command[0] == '\0')
    return -1;

  pid_t pid;
  int status;
  int ret;

  if ((pid = fork()) == 0)
  {
    printf("Executing child process. PID: %ld.\n", (long)getpid());
    ret = execvp(command, arguments);
    // Should not get here
    if (ret != 0)
      printf("Could not run command.\n");
    exit(ret);
  }
  else if (pid > 0)
  {
    // Parent waits for process to complete.
    printf("Waiting for child process in parent. PID: %ld.\n", (long)getppid());
    wait(&status);
    ret = WEXITSTATUS(status);
  }
  else
  {
    ret = -1;
  }
  return ret;
}