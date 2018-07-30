#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#define SLEEP_INTERVAL 2
#define CAPACITY 1000

struct Manufacturer
{
  int itemsGiven;
  int items;
};

struct Salesman
{
  char name;
  double takes;
};

void *getShirts();

struct Manufacturer mfr;

int main()
{
  pthread_t tid[3];

  mfr.itemsGiven = 0;
  mfr.items = CAPACITY;
  struct Salesman s1 = {'A', 0.33};
  struct Salesman s2 = {'B', 0.25};
  struct Salesman s3 = {'C', 0.2};

  pthread_setconcurrency(3);

  pthread_create(&tid[0], NULL, (void *(*)(void *))getShirts, &s1);
  pthread_create(&tid[1], NULL, (void *(*)(void *))getShirts, &s2);
  pthread_create(&tid[2], NULL, (void *(*)(void *))getShirts, &s3);

  for (int i = 0; i < 3; i++)
       pthread_join(tid[i], NULL);
  printf("The total number of T-shirts given out it: %d\n", mfr.itemsGiven);
  exit(EXIT_SUCCESS);
}

void *getShirts(struct Salesman *s)
{
  while (mfr.items > 0)
  {
    sleep(SLEEP_INTERVAL);
    int remItems = (int) ceil(mfr.items * s->takes);
    mfr.items -= remItems;
    printf("%c takes away %d T-shirts.\n", s->name, remItems);
    mfr.itemsGiven += remItems;
  }
  return 0;
}
