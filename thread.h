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
bool sleeping = false, customereating= true;
static int cust0eat = 0,cust1eat = 0,cust2eat = 0;

void *chefThread(void *arg)
{
    srand(time(NULL));
    sem_wait(&kitchen);
    while(1)
    {
        if(times == 100)
        {
            sleep(0.5);
            printf("Customer 0 gets to eat %d times\n", cust0eat);
            printf("Customer 1 gets to eat %d times\n", cust1eat);
            printf("Customer 2 gets to eat %d times\n", cust2eat);
            exit(0);
        }
        if(customereating == true)
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

        sleeping = true;
        customereating = false;

        times++;
        }
        sem_post(&kitchen);
    }
}

void *customerThread(void *arg)
{
    sem_wait(&kitchen);
    while(1)
    {
       
        if(customereating == false)
        {
            if(sleeping && threadcheck1 != (int)arg && treadcheck2 != (int)arg)
            {
                printf("Customer %d gets to eat\n", (int)arg);
                printf("\n");
                if((int) arg == 0)
                {
                    cust0eat++;
                }
                else if((int) arg == 1)
                {
                    cust1eat++;
                }
                else if((int) arg == 2)
                {
                    cust2eat++;
                }
              sleeping = false;
              customereating = true;
            }
        }
        sem_post(&kitchen);
    }
}