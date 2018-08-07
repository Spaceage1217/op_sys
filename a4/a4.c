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

/*  runOPT:
 *    Process the reference string using the Optimal
 *    algorithm. Prints the ref string, each step of 
 *    the iteration, and the state of the page table
 *    after each ref string.
 */
int runOPT(int refString[]);

/*  runLRU:
 *    Process the reference string using the Least Recently
 *    Used (LRU) algorithm. Prints the ref string, each step 
 *    of the iteration, and the state of the page table after
 *    each ref string.
 */
int runLRU(int refString[]);

/*  findNextIndex: (Optimal Algorithm Helper)
 *    From the starting index, find the next instance of
 *    the argument in the args. Return the location of the
 *    next instance of the arg, or a sufficiently large number
 *    to indicate the arg is not present in the list.
 */
int findNextIndex(const int args[], int arg, int startIdx);

/*  getMaxIndex:  (LRU Algorithm Helper)
 *    Find the frame in the frames that has the largest
 *    timeSinceRef. Returns the index of that frame.
 */
int getMaxIndex(struct Frame frames[]);


int main()
{
  // INIT
  // Seed rand -> Unique sequence
  srand(time(0));
  REFSTRINGLEN = rand() % MAX;
  int faultsLRU, 
      faultsOPT, 
      frames, i;
  int refString[REFSTRINGLEN];
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
      "\nOptimal had: [ %d ] faults,\nand\n"
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
  printf("\n\n");

  for (i = 0; i < REFSTRINGLEN; i++)
  {
    swap = true;
    ref = refString[i];
    printf("Checking if %d is in page table.\n", ref);
    for (j = 0; j < FRAMES; j++)
    {
      // Update the reference if the page hits
      if (swap && frames[j].pageNum == ref)
      {
        frames[j].timeSinceRef = 1;
        swap = false;
        printf("Page found: No page fault.\n");
      }
      // Compulsory page faults
      else if (swap && frames[j].pageNum < 0)
      {
        frames[j].pageNum = ref;
        frames[j].timeSinceRef = 1;
        faults++;
        swap = false;
        printf("Page not found: Page fault.\n");
      }
      // Add one tick for each frame
      else
        frames[j].timeSinceRef++;
    }
    if (swap)
    {
      printf("Page not found: Page fault.\n");
      // Find the page with the largest time since
      // being referenced
      k = getMaxIndex(frames);
      frames[k].pageNum = ref;
      frames[k].timeSinceRef = 1;
      faults++;
    }
    printf("Page table contents:\n");
    for (k = 0; k < FRAMES; k++)
      printf("%d ", frames[k].pageNum);
    printf("\n\n");
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
  printf("\n\n");

  for (i = 0; i < REFSTRINGLEN; i++)
  {
    swap = true;
    ref = refString[i];
    printf("Checking if %d is in page table.\n", ref);
    for (j = 0; j < FRAMES; j++)
    {
      // Compulsory page faults
      if (swap && frames[j].pageNum < 0)
      {
        faults++;
        swap = false;
        frames[j].pageNum = ref;
        printf("Page not found: Page fault.\n");
      }
      // Do nothing if page hit
      else if (frames[j].pageNum == ref) 
      {
        swap = false;
        printf("Page found: No page fault.\n");
        break;
      }
    }
    if (swap)
    {
      faults++;
      printf("Page not found: Page fault.\n");
      int nearestIndex[FRAMES];
      int max = 0,
          loc;
      for (k = 0; k < FRAMES; k++)
        nearestIndex[k] = findNextIndex((const int*)refString, frames[k].pageNum, i + 1);
      for (k = 0; k < FRAMES; k++)
      {
        if ( nearestIndex[k] > max ) 
        {
           max = nearestIndex[k];
           loc = k;
        }
      }
      frames[loc].pageNum = ref;
    }
    printf("Page table contents:\n");
    for (k = 0; k < FRAMES; k++)
      printf("%d ", frames[k].pageNum);
    printf("\n\n");
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

int findNextIndex(const int args[], int arg, int startIdx)
{
  int i;
  for (i = startIdx; i < REFSTRINGLEN; i++)
    if (args[i] == arg) return i;
  return REFSTRINGLEN;
}