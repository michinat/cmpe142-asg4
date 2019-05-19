#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h> 

char* item[3] = {"Hamburger", "Fries", "Soda"};
sem_t kitchen;
int times = 0;
int randNum,randNum1;

void chefThread(void *arg)
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
        
        printf("Chef cooks: %s and %s", item[randNum], item[randNum1]);

        times++;
    }
    sem_post(&kitchen);
}

int main(void)
{
 sem_init (&kitchen, 0, 1);   
}