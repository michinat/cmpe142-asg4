#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdbool.h> 
#include <time.h>
#include <unistd.h>

char* item[] = {"Hamburger", "Fries", "Soda"};
sem_t kitchen;
int times = 0;
int randNum,randNum1;
int threadcheck1, treadcheck2;
bool chefDone = false, eating= true;

void *chefThread(void *arg)
{
    srand(time(NULL));
    sem_wait(&kitchen);
    while(1)
    {
        sleep(1);
        if(times == 3)
        {
            exit(0);
        }
        if(eating == true)
        {
            randNum = rand()%3;
            randNum1 = rand()%3;
        while(randNum == randNum1)
        {
            randNum1 = rand()%3;
        }

        threadcheck1 = randNum;
        treadcheck2 = randNum1;

        printf("Chef cooks: %s and %s\n", item[randNum], item[randNum1]);

        chefDone = true;
        eating = false;

        times++;
        }
        sem_post(&kitchen);
    }
}

void *customerThread(void *arg)
{
    while(1)
    {
       sleep(1);
       sem_wait(&kitchen);
        if(eating == false)
        {
            if(chefDone && threadcheck1 != (int)arg && treadcheck2 != (int)arg)
            {
              printf("Customer %d completed eating\n", (int)arg);
              printf("\n");
              chefDone = false;
              eating = true;
            }
        }
        sem_post(&kitchen);
    }
    
}

int main(void)
{
    pthread_t cust0,cust1,cust2,chef;
    sem_init (&kitchen, 0, 1);

    printf("Customer 0 has infinite Hamburger\n");
    printf("Customer 1 has infinite Fries\n");
    printf("Customer 2 has infinite Soda\n");
    printf("\n");

    pthread_create(&chef,0,chefThread,0);

    pthread_create(&cust0,0,customerThread,(void*)0);
    pthread_create(&cust1,0,customerThread,(void*)1);
    pthread_create(&cust2,0,customerThread,(void*)2);

    while(1);
}