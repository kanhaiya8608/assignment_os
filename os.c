#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t numcats,nummice;
int numfood=0,fcount=0;
void *cats(void *arg)
{
  int x;
 x = ((int)arg);
sem_wait(&numcats);
  fcount = fcount + 1;
 numfood++;
  if(fcount==1)
sem_wait(&nummice);
printf("the cat %d eats food %d\n",x,numfood);
  sleep(4);
  sem_post(&numcats);
sem_wait(&numcats);
  fcount = fcount - 1;
  if(fcount==0)
 sem_post(&nummice);
  sem_post(&numcats);
  }
 void *mice(void *arg)
  {
int x;
  x = ((int) arg);
  sem_wait(&nummice);
 printf("the mice %d eats food %d\n",x,numfood);
  sleep(2);
  sem_post(&nummice);
  }
void   main()
  {
  int i;
  pthread_t th1[5],th2[5];
 sem_init(&numcats,0,1);
  sem_init(&nummice,0,1);
for(i=0;i<=2;i++)
 {
  pthread_create(&th1[i],NULL,cats,(void *)i);
  pthread_create(&th2[i],NULL,mice,(void *)i);
  }
for(i=0;i<=2;i++)
  {
  pthread_join(th1[i],NULL);
  pthread_join(th2[i],NULL);
  }
}
