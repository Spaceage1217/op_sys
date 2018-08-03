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

void *getShirts();

struct Manufacturer mfr;

int main()
{
  mfr.itemsTaken = 0;
  mfr.items = CAPACITY;

  struct Salesman s1 = { 0, 'A', 0.33, 1 };
  struct Salesman s2 = { 0, 'B', 0.25, 2 };
  struct Salesman s3 = { 0, 'C', 0.20, 0 };

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
    int remItems = (int)ceil(mfr.items * s->takes);
    if (s->delay > 0) sleep(s->delay);
    mfr.items -= remItems;

    printf("%c takes away %d T-shirts.\n", s->name, remItems);
    shirtsTaken += remItems;
  }
  mfr.itemsTaken += shirtsTaken;
  return 0;
}
