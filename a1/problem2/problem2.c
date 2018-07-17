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


int main(int argc, char* argv[]) {
   pid_t prePid,
         sortPid;
   int preStatus;
   int pp[2];
   if (pipe(pp) < 0) return 1;
   if ((prePid = fork()) == 0) 
   { // execute pre
      dup2(pp[0], 0);
      dup2(pp[1], 1);
      close(pp[0]);
      close(pp[1]);
      char* argv[] = { "./pre", NULL };
      execvp(argv[0], argv);
   }

   // Prevent race condition between pre and sort
   if ((waitpid(prePid, &preStatus, 0) == prePid) && (preStatus != 0)) 
      perror("Pre process.\n");
   else printf("Pre process exit status: %X\n", WEXITSTATUS(preStatus));

   if ((sortPid = fork()) == 0) 
   { // execute sort
      dup2(pp[0], 0);
      close(pp[0]);
      close(pp[1]);
      char* argv[] = { "./sort", NULL };
      execvp(argv[0], argv);
   }
   close(pp[0]);
   close(pp[1]);

   // Exit from the parent process
   exit(EXIT_SUCCESS);
}
