#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h> 
#include <stdbool.h> 

char* item[3] = {"Hamburger", "Fries", "Soda"};
sem_t kitchen;
int times = 0;
int randNum,randNum1;
bool chefDone, custDone, eating;

void *chefThread(void *arg)
{
    srand(time(NULL));
    sem_wait(&kitchen);
    while(times != 100)
    {
        for(int i = 0;i<2;i++)
        {
            randNum = rand()%3;
            randNum1 = rand()%3;
            while(randNum == randNum1)
            {
                randNum1 = rand()%3;
            }
        }
        
        printf("Chef cooks: %s and %s\n", item[randNum], item[randNum1]);
        chefDone = 1;
        eating = 0;

        times++;
    }
    sem_post(&kitchen);
}

void *customerThread(void *arg)
{
    while(1)
    {
        if(!eating)
        {
            sem_wait(&kitchen);
            if(chefDone && randNum != (int)arg && randNum1 != (int)arg)
            {
              printf("Customer %d completed eating\n", (int)arg);
            }
            chefDone = 0;
            eating = 1;
        }
        sem_post(&kitchen);
    }
}

int main(void)
{
    pthread_t cust1,cust2,cust3,chef;
    sem_init (&kitchen, 0, 1);   
    printf("Customer 1 has hamburger\n");
    printf("Customer 2 has fries\n");
    printf("Customer 3 has soda\n");
    pthread_create(&chef,0,chefThread,0);
    pthread_create(&cust1,0,customerThread,(void*)0);
    pthread_create(&cust2,0,customerThread,(void*)1);
    pthread_create(&cust3,0,customerThread,(void*)2);
}