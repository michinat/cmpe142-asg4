#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdbool.h> 
#include <time.h>
#include <unistd.h>
#include "thread.h"

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