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

struct Frame
{
  int timeSinceRef;
  int pageNum;
};

int runOPT(int refString[]);
int runLRU(int refString[]);
int findNextIndex(const char args[], int arg, int startIdx);
int getMaxIndex(struct Frame frames[]);

int main()
{
  // INIT
  // Seed rand -> Unique sequence
  srand(time(0));
  int faultsLRU, faultsOPT, frames;
  // int refLength = rand() % MAX;
  REFSTRINGLEN = 10;
  int refString[REFSTRINGLEN];
  int i;
  for (i = 0; i < REFSTRINGLEN; i++)
    refString[i] = (int)(rand() % 5) + 1;

  // Get # of frames
  printf("Enter the number of frames: ");
  scanf("%d", &frames);
  FRAMES = frames;

  // Test LRU
  faultsLRU = runLRU(refString);

  // Test Optimal
  faultsOPT = runOPT(refString);

  printf(
      "Optimal had: [ %d ] faults,\nand\n"
      "LRU had: [ %d ] faults.\n",
      faultsOPT, faultsLRU);
  exit(EXIT_SUCCESS);
}

int runLRU(int refString[])
{
  // INIT
  int faults = 0,
      i, j, k,
      ref;
  bool swap;
  struct Frame frames[FRAMES];
  for (i = 0; i < FRAMES; i++)
    frames[i].pageNum = -1;

  printf("Running LRU for reference string:\n");
  for (i = 0; i < REFSTRINGLEN; i++)
    printf("%d ", refString[i]);
  printf("\n");

  for (i = 0; i < REFSTRINGLEN; i++)
  {
    swap = true;
    ref = refString[i];
    printf("Checking if %d is in page table.\n", ref);
    for (j = 0; j < FRAMES; j++)
    {
      if (swap && frames[j].pageNum == ref)
      {
        frames[j].timeSinceRef = 1;
        swap = false;
        printf("found a page\n");
      }
      else if (swap && frames[j].pageNum < 0)
      {
        frames[j].pageNum = ref;
        frames[j].timeSinceRef = 1;
        faults++;
        swap = false;
        printf("set empty %d\n", j);
      }
      else
      {
        frames[j].timeSinceRef++;
        printf("incrementing page\n");
      }
    }
    if (swap)
    {
      printf("swapping\n");
      k = getMaxIndex(frames);
      frames[k].pageNum = ref;
      frames[k].timeSinceRef = 1;
      faults++;
    }
    for (k = 0; k < FRAMES; k++)
      printf("%d ", frames[k].pageNum);
    printf("\n");
  }
  return faults;
}

int runOPT(int refString[])
{
  // INIT
  int faults = 0,
      i, j, k,
      ref;
  bool swap;
  struct Frame frames[FRAMES];
  for (i = 0; i < FRAMES; i++)
    frames[i].pageNum = -1;

  printf("\nRunning OPTIMAL for reference string:\n");
  for (i = 0; i < REFSTRINGLEN; i++)
    printf("%d ", refString[i]);
  printf("\n");

  for (i = 0; i < REFSTRINGLEN; i++)
  {
    swap = true;
    ref = refString[i];
    printf("Checking if %d is in page table.\n", ref);
    for (j = 0; j < FRAMES; j++)
    {
      if (swap && frames[j].pageNum < 0)
      {
        faults++;
        swap = false;
        frames[j].pageNum = ref;
        printf("set empty %d\n", j);
      }

      if (frames[j].pageNum == ref) 
      {
        swap = false;
        printf("found match\n");
        break;
      }
    }
    if (swap)
    {
      faults++;
      int nextIdx,
          maxIdx,
          maxFrame;

      maxIdx = maxFrame = 0;
      for (k = 0; k < FRAMES; k++)
      {
        nextIdx = findNextIndex((const char*)refString, frames[k].pageNum, i);
        printf("Highest idx for %d is %d\n", k, maxIdx);
        printf("Current frame %d\n", k);
        if (nextIdx > maxIdx)
        {
          maxIdx = nextIdx;
          maxFrame = k;
        }
      }
      frames[maxFrame].pageNum = ref;
      printf("swapping %d %d\n", maxFrame, ref);
      printf("looking ahead and swapping\n");
    }
    for (k = 0; k < FRAMES; k++)
      printf("%d ", frames[k].pageNum);
    printf("\n");
  }
  return faults;
}

int getMaxIndex(struct Frame frames[])
{
  int maximum = frames[0].timeSinceRef,
      c,
      location = 0;

  for (c = 1; c < FRAMES; c++)
  {
    if (frames[c].timeSinceRef > maximum)
    {
      maximum = frames[c].timeSinceRef;
      location = c;
    }
  }
  return location;
}

int findNextIndex(const char args[], int arg, int startIdx)
{
  int i;
  for (i = startIdx; i < REFSTRINGLEN; i++)
  {
    printf("%d match\n", args[i] == arg);
    if (args[i] == arg) {
      return i;
    }
  }
  printf("return not found\n");
  return -1;
}