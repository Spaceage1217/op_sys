/*
  Assignment 4
  a4.c
  Developer: Michael Scales
  Operating Systems
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


#define MAX 30;

int FRAMES;
int REFSTRINGLEN;

int runOPT(char refString[], int length);
int runLRU(char refString[], int length);

int main()
{
  // INIT
  // Seed rand -> Unique sequence
  srand(time(0));
  int faultsLRU, faultsOPT, frames;
  // int refLength = rand() % MAX;
  int refLength = 5;
  char refString[refLength];
  int i;
  for (i = 0; i < refLength; i++)
    refString[i] = (int)(rand() % 5) + 1;

  // Get # of frames
  printf("Enter the number of frames: ");
  scanf("%d", &frames);
  FRAMES = frames;

  // Test LRU
  faultsLRU = runLRU(refString, refLength);

  // Test Optimal
  faultsOPT = runOPT(refString, refLength);

  printf(
    "Optimal had: [ %d ] faults,\nand\n"
    "LRU had: [ %d ] faults.\n", faultsOPT, faultsLRU
  );
  exit(EXIT_SUCCESS);
}

int runLRU(char refString[], int length)
{
  // INIT
  int faults = 0,
      LRU = 0,
      i, j, k;
  char frameArray[FRAMES];
  char ref, page;
  bool fault;
  printf("Running LRU for reference string:\n");
  for (i = 0; i < length; i++)
    printf("%d ", refString[i]);
  printf("\n");

  for (i = 0; i < length; i++) {
    fault = false;
    ref = refString[i];
    printf("Checking if %d is in page table.\n", ref);
    for (j = 0; j < FRAMES; j++) {
      page = frameArray[j];
      if (ref == page) {
        printf("page found\n");
        break;
      }
      else
      {
        printf("not found\n");
        // Not found -> replace
        if (j == (FRAMES - 1)) {
          fault = true;
          break;
        }
      }
    }
    if (fault) {
      printf("replacing page\n");
      if (LRU < 3)
        frameArray[LRU++] = ref;
    } else printf("Page present. moving on\n");
    for (k = 0; k < FRAMES; k++)
      printf("%d ", frameArray[i]);
    printf("\n");
  }
  return faults;
}

int runOPT(char refString[], int length)
{
  // INIT
  int faults = 0;
  return faults;
}