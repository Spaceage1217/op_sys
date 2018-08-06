/*
  Assignment 3
  threadPartB.c
  Developer: Michael Scales
  Operating Systems
*/
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 1000

struct Manufacturer
{
  int itemsTaken;
  int items;
};

struct Salesman
{
  pthread_t tid;
  char name;
  double takes;
  int delay;
};

/*  getShirts:
 *    A salesman is sent to get shirts from the manufacturer.
 *    They will get their shirts, sleep, and then put there shirts
 *    in the items they're taking.
 */
void *getShirts();

// Global: Share with all Salespeople
struct Manufacturer mfr;
pthread_mutex_t mutex;

int main()
{
  mfr.itemsTaken = 0;
  mfr.items = CAPACITY;

  // Salesman: integer thread id, name, percentage 
  // of shirts to take, and integer delays
  struct Salesman s1 = { 0, 'A', 0.33, 1 };
  struct Salesman s2 = { 0, 'B', 0.25, 1 };
  struct Salesman s3 = { 0, 'C', 0.20, 2 };

  pthread_setconcurrency(3);

  pthread_create(&s1.tid, NULL, (void *(*)(void *))getShirts, &s1);
  pthread_create(&s2.tid, NULL, (void *(*)(void *))getShirts, &s2);
  pthread_create(&s3.tid, NULL, (void *(*)(void *))getShirts, &s3);

  pthread_join(s1.tid, NULL);
  pthread_join(s2.tid, NULL);
  pthread_join(s3.tid, NULL);

  printf("The total number of T-shirts given out is: %d\n", mfr.itemsTaken);
  exit(EXIT_SUCCESS);
}

void *getShirts(struct Salesman *s)
{
  int shirtsTaken = 0;
  while (mfr.items > 1)
  {
    pthread_mutex_lock(&mutex);
    int remItems = (int)ceil(mfr.items * s->takes);
    if (s->delay > 0) sleep(s->delay);
    mfr.items -= remItems;
    pthread_mutex_unlock(&mutex);

    printf("%c takes away %d T-shirts.\n", s->name, remItems);
    shirtsTaken += remItems;
  }
  mfr.itemsTaken += shirtsTaken;
  return 0;
}
