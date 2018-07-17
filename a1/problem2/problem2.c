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
   if ((prePid = fork()) == 0) { // execute pre
      dup2(pp[1], 1);
      close(pp[0]);
      close(pp[1]);
      char* argv[] = { "./pre", NULL };
      execvp(argv[0], argv);
   }

   // Prevent race condition between pre and sort
   if ((waitpid(prePid, &preStatus, 0) == prePid) && (preStatus != 0)) perror("Child1 process.\n");
   else printf("child exit status:0x %X\n", WEXITSTATUS(preStatus));

   if ((sortPid = fork()) == 0) { // execute sort
      printf("Starting child2.\nWaiting for input from child1.\n");
      dup2(pp[0], 0);
      close(pp[0]);
      close(pp[1]);
      printf("Printing output from child1 inside child2.\n");
      char buf[500];
      int len;
      while ((len=read(0, buf, 500)) > 0) write(1, buf, len);
      printf("Returning from child2.\n");
      exit(EXIT_SUCCESS);
   }
   close(pp[0]);
   close(pp[1]);
   exit(EXIT_SUCCESS);
}
